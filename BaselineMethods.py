# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
from ProcessFiles import _pen
from ProcessFiles import *
from pythonrouge.pythonrouge import Pythonrouge

baseline_dir = os.path.join(os.getcwd(), 'Baseline_Results')
fid_baseline_dir = os.path.join(baseline_dir, 'fid_baselines')
fid_baseline_pkdir = os.path.join(fid_baseline_dir, 'PickleFiles')
rouge_xml_dir = os.path.join(fid_baseline_dir, 'align_xml')
cc_baseline_dir = os.path.join(baseline_dir, 'cc_baselines')
ch_baseline_dir = os.path.join(baseline_dir, 'ch_baselines')
ch_baseline_pkdir = os.path.join(ch_baseline_dir, 'PickleFiles')


def GetACLAIinfoForBaselines(dataset, hyp_ftype, ref_ftype):
    if dataset == 'acl':
        hyp_dir = acl_fsdir[hyp_ftype][1]
        hyp_fnpt = acl_snpt
        pk_dir = acl_pkdir
        if type(ref_ftype) is str:
            ref_dir = acl_fsdir[ref_ftype][1]
            ref_fnpt = acl_std_snpt
        else:
            ref_dir = acl_fsdir[ref_ftype[0]][1]
            ref_fnpt = '\\.'.join(acl_snpt.split('\\.')[:-1] + [ref_ftype[1]])
    elif dataset == 'ai':
        hyp_dir = ai_fsdir[hyp_ftype][1]
        hyp_fnpt = ai_snpt
        pk_dir = ai_pkdir
        if type(ref_ftype) is str:
            ref_dir = ai_fsdir[ref_ftype][1]
            ref_fnpt = ai_std_snpt
        else:
            ref_dir = ai_fsdir[ref_ftype[0]][1]
            ref_fnpt = '\\.'.join(ai_snpt.split('\\.')[:-1] + [ref_ftype[1]])
    else:
        print("Just For ACL and AI Dataset!")
        return None
    return pk_dir, ref_dir, hyp_dir, 'p', ref_fnpt, hyp_fnpt


def get_fid_basefn(dataset, basetype, Ftypes, ref_ftype, _stem, _stopw, fn_suffix='.pk'):
    ftype_str = Ftypes if isinstance(Ftypes, str) else '-'.join(Ftypes)
    ref_str = ref_ftype if isinstance(ref_ftype, str) else '-'.join(ref_ftype)
    stem_str = 'stem' if _stem else 'nostem'
    stopw_str = 'stop' if _stopw else 'nostop'
    return '_'.join([dataset.upper(), basetype, ftype_str, ref_str, stem_str, stopw_str]) + fn_suffix


def get_cc_basefn(dataset, basetype, Ftypes, pen_gap, _stem, _stopw, fn_suffix='.pk'):
    ftype_str = Ftypes if isinstance(Ftypes, str) else '-'.join(Ftypes)
    pen_str = 'pen' if pen_gap else 'no-pen'
    stem_str = 'stem' if _stem else 'nostem'
    stopw_str = 'stop' if _stopw else 'nostop'
    return '_'.join([dataset.upper(), basetype, ftype_str, pen_str, stem_str, stopw_str]) + fn_suffix


#######################################################################################
# -------------------------------------- ROUGE -------------------------------------- #
#######################################################################################
def CallRougeForOneSum(hyp_sents, ref_sents, _ngram=1, _l=False, _w=False, _su4=False, _stem=True, _stopw=True,
                       _lenlmt=False, _len=200):
    rouge = Pythonrouge(summary_file_exist=False, summary=[hyp_sents], reference=[ref_sents], xml_dir=rouge_xml_dir,
                        n_gram=_ngram, ROUGE_L=_l, ROUGE_W=_w, ROUGE_SU4=_su4,
                        stemming=_stem, stopwords=_stopw, length_limit=_lenlmt, length=_len)
    score = rouge.calc_score()
    return score


def CallRougeForAlignSum(hyp_ref_fpalign_dict, pkdir, **kwargs):
    hyp_ref_rouge_dict = {}
    for hfp, rfps in hyp_ref_fpalign_dict.items():
        hyp_sents, ref_sents = GetFileCacheDatas(hfp, "Sents", pkdir), []
        if not hyp_sents:
            continue
        ref_wnum_thr = sum([len(DelEmptyString(sent.split(' '))) for sent in hyp_sents])*1.25
        for fp in rfps:
            temp_sents, temp_wnum = [], 0
            for sent in GetFileCacheDatas(fp, "Sents", pkdir):
                temp_sents.append(sent)
                temp_wnum += len(DelEmptyString(sent.split(' ')))
                if temp_wnum > ref_wnum_thr:
                    break
            if len(temp_sents) > 0:
                ref_sents.append(temp_sents)
        if not ref_sents:
            continue
        rouge_dict = CallRougeForOneSum(hyp_sents, ref_sents, **kwargs)
        hyp_ref_rouge_dict[os.path.basename(hfp), '; '.join([os.path.basename(fp) for fp in rfps])] = rouge_dict
    return hyp_ref_rouge_dict


def CallRougeForAIACL(dataset, Ftypes, ref_ftype, _ngram=2, _l=True, _w=False, _su4=True, _stem=True, _stopw=True,
                      _lenlmt=False, _len=200):
    kwargs = locals()
    for _key in ['dataset', 'Ftypes', 'ref_ftype']:
        kwargs.pop(_key)

    rouge_pkfp = os.path.join(fid_baseline_pkdir, get_fid_basefn(dataset, 'rouge', Ftypes, ref_ftype, _stem, _stopw))
    if os.path.isfile(rouge_pkfp):
        return Loadpickle(rouge_pkfp)

    ref_hyp_rouge_dict = {}
    for ftype in Ftypes:
        try:
            pk_dir, ref_dir, hyp_dir, sumtype, ref_fnpt, hyp_fnpt = GetACLAIinfoForBaselines(dataset, ftype, ref_ftype)
        except:
            continue
        hyp_ref_fpalign_dict = AlignSrcSum(hyp_dir, ref_dir, hyp_fnpt, ref_fnpt, sumtype)
        hyp_ref_rouge_dict = CallRougeForAlignSum(hyp_ref_fpalign_dict, pk_dir, **kwargs)
        for (hypfn, reffns), rouge_dict in hyp_ref_rouge_dict.items():
            if reffns not in ref_hyp_rouge_dict:
                ref_hyp_rouge_dict[reffns] = {}
            ref_hyp_rouge_dict[reffns][hypfn] = rouge_dict

    Dumppickle(rouge_pkfp, ref_hyp_rouge_dict)
    return ref_hyp_rouge_dict


def CallRougeForDUC(sumfn_refID_dict, ftype='p100', refopt='same', _ngram=2, _l=True, _w=False, _su4=True,
                    _stem=True, _stopw=True, _lenlmt=False, _len=200):
    kwargs = locals()
    for _key in ['sumfn_refID_dict', 'ftype', 'refopt']:
        kwargs.pop(_key)

    rouge_pkfp = os.path.join(fid_baseline_pkdir, get_fid_basefn('DUC', 'rouge', ftype, refopt, _stem, _stopw))
    if os.path.isfile(rouge_pkfp):
        return Loadpickle(rouge_pkfp)

    sumfn_rouges = {}
    for sumfn, refIDs in sumfn_refID_dict.items():
        sum_sents = GetFileCacheDatas(os.path.join(duc_fsdir[ftype][1], sumfn), 'Sents', duc_pkdir)
        if not sum_sents:
            continue
        ref_sents = []
        for sysid in refIDs:
            reffn = '.'.join(sumfn.split('.')[:-1]) + '.' + sysid
            temp_sents = GetFileCacheDatas(os.path.join(duc_fsdir[ftype][1], reffn), 'Sents', duc_pkdir)
            if temp_sents:
                ref_sents.append(temp_sents)
        sumfn_rouges[sumfn] = CallRougeForOneSum(sum_sents, ref_sents, **kwargs)

    Dumppickle(rouge_pkfp, sumfn_rouges)
    return sumfn_rouges


#######################################################################################
# --------------------------------- BLEU metric ------------------------------------- #
#######################################################################################
def CallBleuForOneSum(hyp_sents, ref_sents_list, _stem=True, _stopw=True, _ngram=4):
    hyp_words = ProcessTxt2Words(' '.join(hyp_sents).lower(), _stem, _stopw)
    ref_words_list = [ProcessTxt2Words(' '.join(sents).lower(), _stem, _stopw) for sents in ref_sents_list]
    chencherry = SmoothingFunction()
    bleu_n2vals = {}
    for n in range(1, _ngram + 1):
        _val = sentence_bleu(ref_words_list, hyp_words, tuple([1 / n] * n), smoothing_function=chencherry.method1)
        bleu_n2vals['BLEU-' + str(n)] = float(_val)
    return bleu_n2vals


def CallBleuForAlignSum(hyp_ref_fpalign_dict, pkdir, **kwargs):
    hyp_ref_bleu_dict = {}
    for hfp, rfps in hyp_ref_fpalign_dict.items():
        hyp_sents, ref_sents_list = GetFileCacheDatas(hfp, "Sents", pkdir), []
        if not hyp_sents:
            continue
        ref_wnum_thr = sum([len(DelEmptyString(sent.split(' '))) for sent in hyp_sents])*1.25
        for fp in rfps:
            temp_sents, temp_wnum = [], 0
            for sent in GetFileCacheDatas(fp, "Sents", pkdir):
                temp_sents.append(sent)
                temp_wnum += len(DelEmptyString(sent.split(' ')))
                if temp_wnum > ref_wnum_thr:
                    break
            if len(temp_sents) > 0:
                ref_sents_list.append(temp_sents)
        if not ref_sents_list:
            continue
        bleu_dict = CallBleuForOneSum(hyp_sents, ref_sents_list, **kwargs)
        hyp_ref_bleu_dict[os.path.basename(hfp), '; '.join([os.path.basename(fp) for fp in rfps])] = bleu_dict
    return hyp_ref_bleu_dict


def CallBleuForAIACL(dataset, Ftypes, ref_ftype, _ngram=4, _stem=True, _stopw=True):
    kwargs = locals()
    for _key in ['dataset', 'Ftypes', 'ref_ftype']:
        kwargs.pop(_key)

    bleu_pkfp = os.path.join(fid_baseline_pkdir, get_fid_basefn(dataset, 'bleu', Ftypes, ref_ftype, _stem, _stopw))
    if os.path.isfile(bleu_pkfp):
        return Loadpickle(bleu_pkfp)

    ref_hyp_bleu_dict = {}
    for ftype in Ftypes:
        try:
            pk_dir, ref_dir, hyp_dir, sumtype, ref_fnpt, hyp_fnpt = GetACLAIinfoForBaselines(dataset, ftype, ref_ftype)
        except:
            continue
        hyp_ref_fpalign_dict = AlignSrcSum(hyp_dir, ref_dir, hyp_fnpt, ref_fnpt, sumtype)
        hyp_ref_bleu_dict = CallBleuForAlignSum(hyp_ref_fpalign_dict, pk_dir, **kwargs)
        for (hypfn, reffns), bleu_dict in hyp_ref_bleu_dict.items():
            if reffns not in ref_hyp_bleu_dict:
                ref_hyp_bleu_dict[reffns] = {}
            ref_hyp_bleu_dict[reffns][hypfn] = bleu_dict

    Dumppickle(bleu_pkfp, ref_hyp_bleu_dict)
    return ref_hyp_bleu_dict


def CallBleuForDUC(sumfn_refID_dict, ftype='p100', refopt='same', _ngram=4, _stem=True, _stopw=True):
    kwargs = locals()
    for _key in ['sumfn_refID_dict', 'ftype', 'refopt']:
        kwargs.pop(_key)

    bleu_pkfp = os.path.join(fid_baseline_pkdir, get_fid_basefn('DUC', 'bleu', ftype, refopt, _stem, _stopw))
    if os.path.isfile(bleu_pkfp):
        return Loadpickle(bleu_pkfp)

    sumfn_bleus = {}
    for sumfn, refIDs in sumfn_refID_dict.items():
        sum_sents = GetFileCacheDatas(os.path.join(duc_fsdir[ftype][1], sumfn), 'Sents', duc_pkdir)
        if not sum_sents:
            continue
        ref_sents =[]
        for sysid in refIDs:
            reffn = '.'.join(sumfn.split('.')[:-1]) + '.' + sysid
            temp_sents = GetFileCacheDatas(os.path.join(duc_fsdir[ftype][1], reffn), 'Sents', duc_pkdir)
            if temp_sents:
                ref_sents.append(temp_sents)
        sumfn_bleus[sumfn] = CallBleuForOneSum(sum_sents, ref_sents, **kwargs)

    Dumppickle(bleu_pkfp, sumfn_bleus)
    return sumfn_bleus


#######################################################################################
# --------------------------- ACL2019 Maxime Peyrard -------------------------------- #
#######################################################################################
def PeyrardForOneSum(sum_sents, src_sents, _stem=True, _stopw=True, a=1, b=1):
    # ---- get distribution of words in the summary ----
    sum_words = ProcessTxt2Words(' '.join(sum_sents), _stem, _stopw)
    sum_wfreqs, sum_wn = Counter(sum_words), len(sum_words)
    if sum_wn > 0:
        for w in sum_wfreqs:
            sum_wfreqs[w] = sum_wfreqs[w]/sum_wn
    # ---- get distribution of words in the source ----
    src_words = ProcessTxt2Words(' '.join(src_sents), _stem, _stopw)
    src_wfreqs, src_wn = Counter(src_words), len(src_words)
    if src_wn > 0:
        for w in src_wfreqs:
            src_wfreqs[w] = src_wfreqs[w]/src_wn
    # ---- Relevance ----
    Rel = 0.0
    for w in (sum_wfreqs & src_wfreqs).keys():
        Rel += sum_wfreqs[w] * np.log2(src_wfreqs[w])
    # ---- Redundancy ----
    negRed = 0.0
    for w in sum_wfreqs:
        negRed -= sum_wfreqs[w] * np.log2(sum_wfreqs[w])
    # ---- Informativeness ----
    know_wfreqs = Counter((sum_wfreqs | src_wfreqs).keys())
    if len(know_wfreqs) > 0:
        for w in know_wfreqs:
            know_wfreqs[w] = know_wfreqs[w] / len(know_wfreqs)
    Inf = 0.0
    for w in (sum_wfreqs & know_wfreqs).keys():
        Inf -= sum_wfreqs[w] * np.log2(know_wfreqs[w])
    # ---- Importance -----
    Imp = negRed + a*Rel + b*Inf

    return {'Relevance': Rel, 'Redundancy': negRed, 'Informative': Inf, 'Importance': Imp}


def CallPeyrardforDataset(dataset, Ftypes, _stem=True, _stopw=True, a=1, b=1):
    kwargs = locals()
    kwargs.pop('dataset')
    kwargs.pop('Ftypes')

    pyrd_pkfp = os.path.join(fid_baseline_pkdir, get_fid_basefn(dataset, 'peyrard', Ftypes, 'noref', _stem, _stopw))
    if os.path.isfile(pyrd_pkfp):
        return Loadpickle(pyrd_pkfp)

    src_sum_peyrard_dict = {}
    for ftype in ([Ftypes] if isinstance(Ftypes, str) else Ftypes):
        try:
            pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
        except:
            continue
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        for srcfp in src_sum_fpalign_dict:
            src_sents = GetFileCacheDatas(srcfp, "Sents", pk_dir)
            srcfn = os.path.basename(srcfp)
            if srcfn not in src_sum_peyrard_dict:
                src_sum_peyrard_dict[srcfn] = {}
            for sumfp in src_sum_fpalign_dict[srcfp]:
                sum_sents = GetFileCacheDatas(sumfp, "Sents", pk_dir)
                src_sum_peyrard_dict[srcfn][os.path.basename(sumfp)] = PeyrardForOneSum(sum_sents, src_sents, **kwargs)

    Dumppickle(pyrd_pkfp, src_sum_peyrard_dict)
    return src_sum_peyrard_dict


#######################################################################################
# ------------------------------- JCD-Disim metric ---------------------------------- #
#######################################################################################
def CallJCDforOneSum(srcfp, sumfp, pkdir, _opts={'JCD-avg'}, pen_gap=True, rdd_thr=0.7, _stem=False, _stopw=False):
    sum_sents = GetFileCacheDatas(sumfp, 'Sents', pkdir)
    # ---- if the summary contains no sent or the only sent has no node, the value of concise is default as 1.0 ----
    if not sum_sents:
        return {_opt: 0.0 for _opt in _opts}
    # ---- if the summary just contains one sentence, get the dis-similarity between the nodes ----
    if len(sum_sents) == 1:
        wlist = ProcessTxt2Words(sum_sents[0], _stem, _stopw)
        if not wlist:
            return {_opt: 0.0 for _opt in _opts}
        else:
            return {_opt: len(Counter(wlist))/len(wlist) for _opt in _opts}

    # ---- if the summary contains more than one sentence ----
    snum = len(sum_sents)
    # -- get the penalty function on sent-gap based on compress rate --
    pen_func = lambda x: 1
    if pen_gap:
        src_sents = GetFileCacheDatas(srcfp, 'Sents', pkdir)
        if not src_sents:
            pen_func = lambda x: _pen(x, snum - 1)
        else:
            pen_func = lambda x: _pen(x, 2 * math.log(len(src_sents), snum))
    # -- get the dis-similarity between the sentences --
    sid2disim = {sid: (1.0, sid) for sid in range(1, snum)}
    for b_sid in range(1, snum):
        b_wlist = ProcessTxt2Words(sum_sents[b_sid], _stem, _stopw)
        if not b_wlist:
            sid2disim[b_sid] = (0.0, b_sid)
            continue
        b_w2f = Counter(b_wlist)
        for a_sid in range(b_sid):
            a_wlist = ProcessTxt2Words(sum_sents[a_sid], _stem, _stopw)
            a_w2f = Counter(a_wlist)
            jcdsim = len(b_w2f & a_w2f) / len(b_wlist)
            if jcdsim < rdd_thr:
                jcdsim = jcdsim * pen_func(b_sid - a_sid - 1)
            _disim = (1 - jcdsim)
            if _disim < sid2disim[b_sid][0]:
                sid2disim[b_sid] = (_disim, a_sid)
    # -- Merge all the dis-similarity of sentence-pairs into conciseness dict --
    return {_opt: match_scores(sid2disim, _opt.split('-')[-1]) for _opt in _opts}


def CallJCDforDataset(dataset='duc', ftype='p100', _opts={'JCD-min', 'JCD-avg', 'JCD-mid'}, pen_gap=True, rdd_thr=0.7,
                      _stem=False, _stopw=False):
    kwargs = locals()
    kwargs.pop('dataset')
    kwargs.pop('ftype')

    jcd_pkfp = os.path.join(cc_baseline_dir, get_cc_basefn(dataset.upper(), 'jcd', ftype, pen_gap, _stem, _stopw))
    if os.path.isfile(jcd_pkfp):
        return Loadpickle(jcd_pkfp)

    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    sumfn_jcds = {}
    for srcfp in src_sum_fpalign_dict:
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sumfn_jcds[os.path.basename(sumfp)] = CallJCDforOneSum(srcfp, sumfp, pk_dir, **kwargs)

    Dumppickle(jcd_pkfp, sumfn_jcds)
    return sumfn_jcds


#######################################################################################
# ----------------------- Information novelty metric -------------------------------- #
#######################################################################################
def CallNoveltyforOneSum(sum_sents, _opts={'Novelty-avg'}, omega=8, _stem=False, _stopw=False):
    # ---- Word count for each sentence ----
    sum_wcounts = [Counter(ProcessTxt2Words(stxt, _stem, _stopw)) for stxt in sum_sents]
    allsn = len(sum_wcounts)

    # ---- get word inverse-sent-frequency, and word-2-index dict ----
    wIsf = Counter()
    for wc in sum_wcounts:
        wIsf.update(wc.keys())
    for w, sn in wIsf.items():
        wIsf[w] = 1 + np.log2(allsn / sn)

    # ---- get vectors for each summary sentence ----
    w2idx = {w: idx for idx, w in enumerate(wIsf.keys())}
    sum_vecs = []
    for wc in sum_wcounts:
        curvec = np.zeros(len(w2idx))
        for w, wn in wc.items():
            curvec[w2idx[w]] = wn * wIsf[w]
        sum_vecs.append(curvec.reshape(1, -1))

    # ---- calculate information novelty score for each sentence ----
    sum_novel = {j: [1.0, j] for j in range(allsn)}
    for i in range(allsn):
        for j in range(i + 1, allsn):
            sum_novel[j][0] -= omega * max(float(cosine_similarity(sum_vecs[i], sum_vecs[j])), 0.0)

    # -- Merge all the dis-similarity of sentence-pairs into conciseness dict --
    return {_opt: match_scores(sum_novel, _opt.split('-')[-1]) for _opt in _opts}


def CallNoveltyforDataset(dataset='duc', ftype='p100', _opts={'Novelty-avg'}, omega=8, _stem=False, _stopw=False):
    kwargs = locals()
    kwargs.pop("dataset")
    kwargs.pop("ftype")

    novel_pkfp = os.path.join(cc_baseline_dir, get_cc_basefn(dataset.upper(), 'novel', ftype, False, _stem, _stopw))
    if os.path.isfile(novel_pkfp):
        return Loadpickle(novel_pkfp)

    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    sumfn_novels = {}
    for srcfp in src_sum_fpalign_dict:
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sum_sents = GetFileCacheDatas(sumfp, "Sents", pk_dir)
            sumfn_novels[os.path.basename(sumfp)] = CallNoveltyforOneSum(sum_sents, **kwargs)

    Dumppickle(novel_pkfp, sumfn_novels)
    return sumfn_novels


#######################################################################################
# ------------------------------ Entity Grid metric --------------------------------- #
#######################################################################################
def LolCHforOneSum(sum_sents, coref_opt=True, dist_opt=False):
    opt_suffix = ("wo" if coref_opt else "w") + ('Dist' if dist_opt else "")
    if len(sum_sents) == 0:
        return {"LocalCoherence-Pu-" + opt_suffix: 0, "LocalCoherence-Pw-" + opt_suffix: 0}
    snum = len(sum_sents)
    sentPG = {sid: {} for sid in range(snum)}
    sentNSet = {sid: set() for sid in range(snum)}
    for sid, stxt in enumerate(sum_sents):
        for w, pos in nltk.pos_tag(nltk.word_tokenize(stxt)):
            if pos in ['NN', 'NNP', 'NNS', 'NNPS', 'PRP', 'PRP$']:
                sentNSet[sid].add(w)
    # ---- project by co-reference words ----
    if coref_opt:
        # ---- get sentence str locations -----
        sentStrPos = {0: [0, 0]}
        for sid, stxt in enumerate(sum_sents[:-1]):
            strnum = len(stxt)
            sentStrPos[sid][1] = sentStrPos[sid][0] + strnum - 1
            sentStrPos[sid + 1] = [sentStrPos[sid][1] + 2, sentStrPos[sid][1] + 2]
        sentStrPos[snum - 1][1] += len(sum_sents[-1]) - 1
        # ---- add links into sentPG by co-references -----
        coref = nlp(' '.join(sum_sents))
        for clust in coref._.coref_clusters:
            tempSID, tempMents = set(), set()
            for mention in clust.mentions:
                tempMents.add(mention.text)
                for sid, [startpos, endpos] in sentStrPos.items():
                    if startpos <= mention.start_char <= endpos:
                        tempSID.add(sid)
            tempSID = sorted(list(tempSID))
            for idx, preid in enumerate(tempSID):
                for nxtid in tempSID[idx+1:]:
                    if nxtid not in sentPG[preid]:
                        sentPG[preid][nxtid] = []
                    sentPG[preid][nxtid].append(tempMents)
    # ---- project by co-occurrence words ----
    else:
        for i in range(snum):
            for j in range(i + 1, snum):
                cowords = sentNSet[i].intersection(sentNSet[j])
                if len(cowords) > 0:
                    sentPG[i][j] = cowords
    PU, PW = 0, 0
    for i in sentPG:
        for j in sentPG[i]:
            if not dist_opt:
                PU += 1
                PW += len(sentPG[i][j])
            else:
                PU += 1 / (j-i)
                PW += len(sentPG[i][j]) / (j-i)
    PU, PW = PU/snum, PW/snum
    return {"LocalCoherence-Pu-"+opt_suffix: PU, "LocalCoherence-Pw-"+opt_suffix: PW}


def CallLolCHforDataset(dataset='duc', Ftypes='p100', coref_opt=True, dist_opt=False):
    kwargs = {"coref_opt": coref_opt, "dist_opt": dist_opt}
    Ftypes = [Ftypes] if isinstance(Ftypes, str) else Ftypes

    opt_suffix = ("_wo" if coref_opt else "_w") + ('_Dist' if dist_opt else "")
    lolch_pkfp = os.path.join(ch_baseline_pkdir, dataset.upper() + '_'.join(Ftypes) + '_lolch_' + opt_suffix + ".pk")
    if os.path.isfile(lolch_pkfp):
        return Loadpickle(lolch_pkfp)

    src_sum_lolch_dict = {}
    for ftype in Ftypes:
        try:
            pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
        except:
            continue
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        for srcfp in src_sum_fpalign_dict:
            srcfn = os.path.basename(srcfp)
            if srcfn not in src_sum_lolch_dict:
                src_sum_lolch_dict[srcfn] = {}
            for sumfp in src_sum_fpalign_dict[srcfp]:
                sum_sents = GetFileCacheDatas(sumfp, "Sents", pk_dir)
                src_sum_lolch_dict[srcfn][os.path.basename(sumfp)] = LolCHforOneSum(sum_sents, **kwargs)

    Dumppickle(lolch_pkfp, src_sum_lolch_dict)
    return src_sum_lolch_dict


#######################################################################################
# ---------------------------------- Test Function ---------------------------------- #
#######################################################################################
def WriteRougeBleuIntoExcel(ref_hyp_rouge_dict, dataset, Ftypes, ref_ftype, _stem=True, _stopw=True,
                            sheet_names=["ROUGE-2-F", "ROUGE-L-F", "ROUGE-SU4-F"]):
    workbook = xlwt.Workbook(encoding='utf-8')
    for sheetname in sheet_names:
        worksheet = workbook.add_sheet(sheetname, cell_overwrite_ok=True)
        reffn_list, sysIDs = sorted(list(ref_hyp_rouge_dict.keys())), {}
        for row, reffn in enumerate(reffn_list):
            worksheet.write(row + 1, 0, reffn)
            for hypfn, rouge_dict in ref_hyp_rouge_dict[reffn].items():
                sysid = hypfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, rouge_dict[sheetname])
        worksheet.write(0, 0, "ref-file-name", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col+1, header, xlwt.easyxf('font: bold on'))

    xls_fname = get_fid_basefn(dataset, sheetname.split('-')[0].lower(), Ftypes, ref_ftype, _stem, _stopw, '.xls')
    workbook.save(os.path.join(fid_baseline_dir, xls_fname))
    return


def WritePeyrardIntoExcel(src_sum_peyrard_dicts, dataset, Ftypes, _stem=True, _stopw=True,
                          sheet_names=['Peyrard-Rel', 'Peyrard-Red', 'Peyrard-Imp']):
    workbook = xlwt.Workbook(encoding='utf-8')
    srcfn_list = sorted(list(src_sum_peyrard_dicts.keys()))

    for sheetname in sheet_names:
        worksheet = workbook.add_sheet(sheetname, cell_overwrite_ok=True)
        for row, srcfn in enumerate(srcfn_list):
            worksheet.write(row + 1, 0, srcfn)
            sysIDs = {}
            for sumfn, pyrd_dicts in src_sum_peyrard_dicts[srcfn].items():
                sysid = sumfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, pyrd_dicts[sheetname])
        worksheet.write(0, 0, "src-file-name", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col + 1, header, xlwt.easyxf('font: bold on'))

    xls_fname = get_fid_basefn(dataset, "peyrard", Ftypes, "noref", _stem, _stopw, '.xls')
    workbook.save(os.path.join(fid_baseline_dir, xls_fname))
    return


def TestNeuralCoref():
    text = 'Barack was born in Hawaii. His wife Michelle was born in Milan. He says that she is very smart.'
    print(f"Input text: {text}")
    coref = nlp(text)
    print(coref._.has_coref)
    print(coref._.coref_clusters)


def TestRouge():
    hyp_sents = [" Tokyo is the one of the biggest city in the world."]
    ref_sents = [["The capital of Japan, Tokyo, is the center of Japanese economy."]]
    score = CallRougeForOneSum(hyp_sents, ref_sents, _l=True, _su4=True)
    print(score)


def TestROUGECorrectFile():
    rouge_correct = ["S000437021300043X", "S0004370213000441", "S000437021300057X", "S0004370213000684"]

    fsdir, pkdir = ai_fsdir, ai_pkdir
    ref_ftype, ref_suffix = 'con', '.xml.C.B'

    for basefn in rouge_correct:
        reffp = os.path.join(fsdir[ref_ftype][1], basefn + ref_suffix)
        all_ref_sents = GetFileCacheDatas(reffp, 'Sents', pkdir)
        for (ftype, suffix) in [('abs', '.xml.A.A'), ('sysA', '.xml.A.30'), ('sysA', '.xml.A.79'), ('sysA', '.xml.A.99')]:
            sumfp = os.path.join(fsdir[ftype][1], basefn + suffix)
            sum_sents = GetFileCacheDatas(sumfp, 'Sents', pkdir)
            ref_wnum_thr = sum([len(DelEmptyString(sent.split(' '))) for sent in sum_sents]) * 1.25
            ref_sents, ref_wnum = [], 0
            for sent in all_ref_sents:
                ref_sents.append(sent)
                ref_wnum += len(DelEmptyString(sent.split(' ')))
                if ref_wnum > ref_wnum_thr:
                    break
            print(suffix.split('.')[-1] + ":", CallRougeForOneSum(sum_sents, [ref_sents], _ngram=2)['ROUGE-2-F'])


def WriteLolCHIntoExcel(dataset, Ftypes, coref_opt=False, dist_opt=False):
    workbook = xlwt.Workbook(encoding='utf-8')

    opt_suffix = ("wo" if coref_opt else "w") + ('Dist' if dist_opt else "")
    sheet_names = ["LocalCoherence-Pu-" + opt_suffix, "LocalCoherence-Pw-" + opt_suffix]

    src_sum_lolch_dict = CallLolCHforDataset(dataset, Ftypes, coref_opt=coref_opt, dist_opt=dist_opt)
    srcfn_list = sorted(list(src_sum_lolch_dict.keys()))
    for sheetname in sheet_names:
        worksheet = workbook.add_sheet(sheetname, cell_overwrite_ok=True)
        sysIDs = {}
        for row, srcfn in enumerate(srcfn_list):
            worksheet.write(row + 1, 0, srcfn)
            for sumfn, lolch_dicts in src_sum_lolch_dict[srcfn].items():
                sysid = sumfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, lolch_dicts[sheetname])
        worksheet.write(0, 0, "src-file-name", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col + 1, header, xlwt.easyxf('font: bold on'))

    xls_fname = '_'.join([dataset.upper(), '_'.join(Ftypes), 'lolch', opt_suffix]) + ".xls"
    workbook.save(os.path.join(ch_baseline_dir, xls_fname))
    return


#######################################################################################
# ----------------------------------- Main Function --------------------------------- #
#######################################################################################
if __name__ == "__main__":
    # TestRouge()
    # TestROUGECorrectFile()
    # TestNeuralCoref()
    dataset, Ftypes, ref_ftype = 'ai', ['abs', 'sysA', 'wstA'], 'sysA'
    _stem, _stopw = True, True
    rouge_dict = CallRougeForAIACL(dataset, Ftypes, ref_ftype, _stem=_stem, _stopw=_stopw)
    WriteRougeBleuIntoExcel(rouge_dict, dataset, Ftypes, ref_ftype, _stem=_stem, _stopw=_stopw)
    bleu_dict = CallBleuForAIACL(dataset, Ftypes, ref_ftype, _stem=_stem, _stopw=_stopw)
    WriteRougeBleuIntoExcel(bleu_dict, dataset, Ftypes, ref_ftype, _stem, _stopw, ["BLEU-1", "BLEU-2", "BLEU-3", "BLEU-4"])
    # dataset, Ftypes = 'duc', ['p100']
    # peyrard_dict = CallPeyrardforDataset(dataset, Ftypes, _stem=_stem, _stopw=_stopw)
    # WritePeyrardIntoExcel(peyrard_dict, dataset, Ftypes, _stem, _stopw, ['Peyrard-Rel', 'Peyrard-negRed', 'Peyrard-Imp'])
    # src_sum_lolch_dict = CallLolCHforDataset(dataset, Ftypes, coref_opt=True, dist_opt=False)
    # WriteLolCHIntoExcel(dataset, Ftypes, coref_opt=True, dist_opt=False)
    # for ftype in ['p100', 'm100', 'm200']:
        # CallJCDforDataset('duc', ftype=ftype)
        # CallPeyrardforDataset('duc', ftype, _stem=_stem, _stopw=_stopw)
        # CallNoveltyforDataset('duc', ftype, _stem=_stem, _stopw=_stopw)
        # CallLolCHforDataset('duc', ftype, coref_opt=True, dist_opt=False)
        # WriteLolCHIntoExcel('duc', [ftype], coref_opt=True, dist_opt=False)