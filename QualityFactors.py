# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
from ProcessFiles import _pen
from ProcessFiles import *
from pylanguagetool import api
import itertools
import pandas as pd


#######################################################################################
# ---------------------------------- Grammar Analysis ------------------------------- #
#######################################################################################
# ---- Analysis a list of sentences and return their grammar scores and grammar errors ----
# -- use LanguageTool: https://github.com/languagetool-org/languagetool
# -- called by the api of pylanguagetool: https://pypi.org/project/pyLanguagetool/0.9.0/
# -- return a dict like {sid:(score:?, errors:? )}
# -- Before running this function, we should first start local language tool HTTP Server By
# java -cp E:\LanguageTool_stable\languagetool-server.jar org.languagetool.server.HTTPServer --port 8081
# -- The manual of local Language Tool http://wiki.languagetool.org/http-server --
def SentsGrammarAnalysis(sents_list):
    print('\t\033[32m%s\033[0m' % "Analysing the Grammar Correctness of sentences ...")
    sents_grammar_dict = {}
    for sid, sent in enumerate(sents_list):
        print('\t\t\033[32m%s\033[0m' % ("Sent ID:" + str(sid)))
        words_list = nltk.word_tokenize(sent)
        # ---- skip the sentence that contains no words ----
        if len(words_list) == 0:
            sents_grammar_dict[sid] = {'score': 0, 'errors': None}
        # ---- Get Grammar Errors for current sentence ----
        else:
            grammar_errors = api.check(sent, "http://localhost:8081/v2/", 'en')['matches']
            sents_grammar_dict[sid] = {'score': 1 - len(grammar_errors) / len(words_list), 'errors': grammar_errors}
    return sents_grammar_dict


def GetDatasetGrammar(src_dir, sum_dir, pk_dir, src_fnpt=r'.+', sum_fnpt=r".+", sumtype='p'):
    print('\033[35m%s\033[0m' % "Getting Summary's Sentence Grammar Dict ...")
    grammar_pkfp = os.path.join(pk_dir, os.path.basename(sum_dir) + "_grammar.pk")
    if os.path.isfile(grammar_pkfp):
        return Loadpickle(grammar_pkfp)
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, src_fnpt, sum_fnpt, sumtype)
    sum_grammar_dict = {}
    for srcfp in src_sum_fpalign_dict:
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sents_list = GetFileCacheDatas(sumfp, 'Sents', pk_dir)
            grammar_dict = SentsGrammarAnalysis(sents_list)
            sum_grammar_dict[os.path.basename(sumfp)] = grammar_dict
    Dumppickle(grammar_pkfp, sum_grammar_dict)
    return sum_grammar_dict


def SingleSumGrammarScore(single_gram_dict, sumfp, pkdir, **kwargs):
    gramTHR = kwargs.get('gramTHR', 0.9)
    Sents = GetFileCacheDatas(sumfp, 'Sents', pkdir, _tab="\t")
    total_wnum, qualified_wnum = 0.0, 0.0
    for sid in single_gram_dict:
        grm_score = single_gram_dict[sid].get('score', 0.0)
        temp_wnum = len(nltk.word_tokenize(Sents[sid]))
        total_wnum += temp_wnum
        if grm_score >= gramTHR:
            qualified_wnum += temp_wnum * grm_score
    return qualified_wnum / total_wnum


def CacheGrammarForDataset(dataset='acl', ftype='abs'):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    print("=========== SumDir:", os.path.basename(sum_dir), "============")
    grammar_dict = GetDatasetGrammar(src_dir, sum_dir, pk_dir, fnpt, snpt, sumtype)
    for sumfn in grammar_dict:
        print("Summary File:", sumfn)
        for sid in grammar_dict[sumfn]:
            print("\tSentID:", sid, "Grammar Score:", grammar_dict[sumfn][sid]['score'])
    return


#######################################################################################
# -------------------------- Extend Object SLNs by similarity links -------------------- #
#######################################################################################
# ----- Get the threshold for find main sentences in the source text -----
# -- The threshold is calculated from the duc_m10 standard summaries to their source text titles --
def GetTHRforMainSent(dataset='duc', ftype='m10', _opt='avg', simtype="mix", _tab=""):
    mainthr_pkfp = os.path.join(corpus_dir, "main_thr_"+_opt+".pk")
    # ---- Load historical main_thr value ----
    if os.path.isfile(mainthr_pkfp):
        return Loadpickle(mainthr_pkfp)
    # ---- Get dataset information from dataset and ftype ----
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    # ---- Calculate the main_thr value ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    s2t_restate = {}
    for srcfp in src_sum_fpalign_dict:
        titSLNs = GetFileCacheDatas(srcfp, 'titSLNs', pk_dir, _tab=_tab)
        if len(titSLNs) == 0:
            continue
        srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', duc_pkdir, _tab=_tab)
        srcfn = os.path.basename(srcfp)
        for sumfp in src_sum_fpalign_dict[srcfp]:
            SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pk_dir, _tab=_tab)
            sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pk_dir, _tab=_tab)
            sumfn = os.path.basename(sumfp)
            temp_restates = {}
            for tidx, tSLN in enumerate(titSLNs):
                nsimM, obj_lab2idx, sum_lab2idx = GetNodeSim(tSLN, SumSLN, simtype, srcVecs, sumVecs, take_freq=False)
                temp_restates[(srcfn, tidx)] = match_scores(greedy_match_pen(nsimM))
            s2t_restate[sumfn] = sorted(temp_restates.items(), key=lambda x: x[1], reverse=True)[0]
    # ---- written restate links into csv tables ----
    csv_string = "Summary_fname, Source_finfo, restate(sum->title)\n"
    for sumfn, ((srcfn, tidx), restate) in s2t_restate.items():
        csv_string += ', '.join([sumfn, srcfn+"--"+str(tidx), "{:.6f}".format(restate)]) + "\n"
    WriteFile(os.path.join(corpus_dir, "mainsent_thr.csv"), csv_string)
    # ---- get the threshold by the way that the option indicates ----
    restate_values = np.sort(np.array([restate for ((srcfn, tidx), restate) in s2t_restate.values()]))
    main_thr = np.average(restate_values)
    if _opt == 'mdn':
        main_thr = np.median(restate_values)
    else:
        try:
            _opt = np.float(_opt)
            if 0 <= _opt <= 1.0:
                main_thr = restate_values[int(len(restate_values) * _opt)]
        except:
            pass
    Dumppickle(mainthr_pkfp, main_thr)
    return main_thr


def GetMainSents(srcfp, pkdir, simtype="mix", main_thr_opt='avg', take_freq=True, _tab=""):
    pkfp = os.path.join(pkdir, '.'.join([os.path.basename(srcfp), main_thr_opt+'MainSents', 'pk']))
    if os.path.isfile(pkfp):
        print(_tab + '\033[35m%s\033[0m' % ("Loading Main Sents for source file " + os.path.basename(srcfp)))
        return Loadpickle(pkfp)
    # ---- create the main sents for current file ----
    print(_tab + '\033[35m%s\033[0m' % ("Geting Main Sents for source file " + os.path.basename(srcfp)))
    main_thr = GetTHRforMainSent(_opt=main_thr_opt, simtype=simtype)
    main_sid2sln_dict = {}
    _tab = _tab + '\t'
    titSLNs = GetFileCacheDatas(srcfp, 'titSLNs', pkdir, _tab=_tab)
    srcSLNs = GetFileCacheDatas(srcfp, 'srcSLNs', pkdir, _tab=_tab)
    srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', pkdir, _tab=_tab)
    # -- return empty dict if the source text has no title or the source text has no SLN list for sents --
    if len(titSLNs) == 0 or len(srcSLNs) == 0:
        print(_tab + '\033[31m%s\033[0m'%("Error! There is no title or no sentences in the source text!"))
        return main_sid2sln_dict
    # -- find main sents by finding the srcsents whose restate link is larger than main_thr --
    for sid, sentSLN in enumerate(srcSLNs):
        temp_restates = []
        for tSLN in titSLNs:
            nsimM, obj_lab2idx, sum_lab2idx = GetNodeSim(tSLN, sentSLN, simtype, srcVecs, srcVecs, take_freq, _tab=_tab)
            temp_restates.append(match_scores(greedy_match_pen(nsimM, _tab=_tab)))
        temp_restates.sort(reverse=True)
        if temp_restates[0] >= main_thr:
            main_sid2sln_dict[sid] = sentSLN
    Dumppickle(pkfp, main_sid2sln_dict)
    return main_sid2sln_dict


def CacheMainSentsForDataset(dataset='acl', ftype='abs', simtype="mix", main_thr_opt='avg', take_freq=True, _tab=""):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    for srcfp in GetFileDirPaths(src_dir)[0]:
        if not re.match(fnpt, os.path.basename(srcfp)):
            continue
        GetMainSents(srcfp, pk_dir, simtype, main_thr_opt, take_freq, _tab)
    return


def GetRelatedSrcSLNs(objSLNs, srcSLNs, restate_thr, objVecs={}, srcVecs={}, simtype="mix", take_freq=False, _tab=""):
    print(_tab + '\033[35m%s\033[0m' % "Get Related source SLNs at THR="+str(restate_thr))
    s2o_restate_dict = {}
    _tab = _tab + '\t'
    # -- return empty dict if the object SLN list contains no SLN  --
    if len(objSLNs) == 0 or len(srcSLNs) == 0:
        print(_tab + '\033[31m%s\033[0m' % "There is no object SLN or no source SLN")
        return s2o_restate_dict
    # -- find main sents by finding the srcsents whose restate link is larger than main_thr --
    for oid, objsln in enumerate(objSLNs):
        for sid, srcsln in enumerate(srcSLNs):
            nsimM, obj_lab2idx, sum_lab2idx = GetNodeSim(objsln, srcsln, simtype, objVecs, srcVecs, take_freq, _tab=_tab)
            temp_restate = match_scores(greedy_match_pen(nsimM, _tab=_tab))
            if temp_restate > restate_thr:
                s2o_restate_dict[(sid, oid)] = temp_restate
    return s2o_restate_dict


# ======== ExtdObjsByRestate: extend object-SLNs by source-sent-SLNs according to restate links =========
# length_thr: the limitation for the total nodes contained by the extended SLNs, default as None
def ExtdObjsByRestate(objSLNs, srcSLNs, restate_thr, objVecs={}, srcVecs={}, length_thr=None, simtype="mix", take_freq=False, _tab=""):
    extdSLNs, extdVecs = [], {}
    extd_nodenum = 0
    s2o_restate_dict = GetRelatedSrcSLNs(objSLNs, srcSLNs, restate_thr, objVecs, srcVecs, simtype, take_freq, _tab=_tab)
    for (sid, oid), restate_val in sorted(s2o_restate_dict.items(), key=lambda x: x[1], reverse=True):
        cursln = srcSLNs[sid]
        if isinstance(length_thr, int) and extd_nodenum + len(cursln) > length_thr:
            break
        extd_nodenum += len(cursln)
        extdSLNs.append(cursln)
        for cur_tuple in GetLabelGenreTuples(cursln, _tab):
            if cur_tuple in objVecs:
                extdVecs[cur_tuple] = objVecs[cur_tuple]
            elif cur_tuple in srcVecs:
                extdVecs[cur_tuple] = srcVecs[cur_tuple]
            else:
                extdVecs[cur_tuple] = None
    return extdSLNs, extdVecs


#######################################################################################
# ---------------- Extend Object SLNs by lead links and restate links --------------- #
#######################################################################################
# ===== extend object-SLNs by source-SLNs according to both restate links and lead links =======
# length_thr: the limitation for the total nodes contained by the extended SLNs, default as None
def ExtdObjsByLead(objSLNs, srcSLNs, restate_thr, objVecs={}, srcVecs={}, ld_ratios=(0.6, 0.4), simtype="mix",
                   take_freq=False, nsim_thr=0.7, nfreq_thr=0, ld_thr=0.4, n_thr=None, _tab=""):
    extdSLNs, extdVecs = [], {}
    # ---- Get lead link parameters ----
    rt_err_flag, ld_ratios = Check_ld_ratio(ld_ratios)
    if rt_err_flag:
        print(_tab + '\033[31m%s\033[0m' % "Errors! ld_ratios should be a tuple/list of positive values to weight lead within different sent_scope!")
        return extdSLNs, extdVecs
    ld_scope = len(ld_ratios)
    # ---- Get Related sentences and sort their ID into sid_series ----
    s2o_restate_dict = GetRelatedSrcSLNs(objSLNs, srcSLNs, restate_thr, objVecs, srcVecs, simtype, take_freq, _tab=_tab)
    related_sids = sorted(list(set([sid for (sid, oid) in s2o_restate_dict])))
    sid_series = MonoIntSeries(related_sids)
    # ---- Get Lead Info List according to sid_series ----
    lead_info_list = [{} for i in range(ld_scope)]
    for sid_seq in sid_series:
        cur_lead_info = GetLeadInfo([srcSLNs[sid] for sid in sid_seq], ld_scope)
        for gap in range(ld_scope):
            for lead_key, lead_times in cur_lead_info[gap].items():
                if lead_key in lead_info_list[gap]:
                    lead_info_list[gap][lead_key] += lead_times
                else:
                    lead_info_list[gap][lead_key] = lead_times
    # ---- merge all extended sentence SLN as a whole SLN, and embed its nodes and links ----
    ExtdSLN = MergeSentsSLN([srcSLNs[sid] for sid in related_sids], "extend")
    # ExtdSLN.showNodes()
    # ---- Add Lead Links into ExtdSLN ----
    for n1 in ExtdSLN.Nodes:
        for n2 in ExtdSLN.Nodes:
            if n1 == n2:
                continue
            ld_weight = GetLeadWeight(n1, n2, lead_info_list, nfreq_thr, ld_ratios)
            if ld_weight > 0:
                ld_link = ThemeLink("LEAD-TO", 'LEAD', 0, n1, n2, ld_weight)
                ExtdSLN.Links.append(ld_link)
    ExtdSLN.adj_matrix = ExtdSLN.BuildAdjMatrix()
    # ExtdSLN.showAdjMatrix()
    # ---- Find most similar nodes for each query nodes in ExtdSLN ----
    o2ex_sim_map = FindSameNodes(MergeSentsSLN(objSLNs), ExtdSLN, simtype, nsim_thr, objVecs, srcVecs)
    # for obj_nlabel, (extd_node, sim_score) in o2ex_sim_map.items():
    #     print(obj_nlabel, "-->", extd_node.nid, ":", extd_node._label, "=", sim_score)
    mapped_extd_nids = set([extd_node.nid for (extd_node, sim_score) in o2ex_sim_map.values()])
    # ---- Get the all the leaded source nodes ----
    # print("==== Out leaded Nodes: ====")
    out_nids_dict = {}
    for map_nid in mapped_extd_nids:
        for extd_node in ExtdSLN.Nodes:
            if map_nid == extd_node.nid:
                continue
            out_nid_key = (map_nid, extd_node.nid)
            for link_value in ExtdSLN.adj_matrix.get(out_nid_key, []):
                if link_value['type'] == 'LEAD' and link_value['times'] > ld_thr:
                    out_nids_dict[out_nid_key] = link_value['times']
    leaded_nids = []
    for (lnid, rnid), ld_weight in sorted(out_nids_dict.items(), key=lambda x: x[1], reverse=True):
        # print(lnid, ExtdSLN.Nodes[lnid]._label, '-->', rnid, ExtdSLN.Nodes[rnid]._label, ':', ld_weight)
        if type(n_thr) is int and n_thr < len(leaded_nids):
            break
        if rnid not in leaded_nids:
            leaded_nids.append(rnid)
    # print("==== In leaded Nodes: ====")
    # in_nids_dict = {}
    # for map_nid in mapped_extd_nids:
    #     for extd_node in ExtdSLN.Nodes:
    #         if map_nid == extd_node.nid:
    #             continue
    #         in_nid_key = (extd_node.nid, map_nid)
    #         for link_value in ExtdSLN.adj_matrix.get(in_nid_key, []):
    #             if link_value['type'] == 'LEAD' and link_value['times'] > lead_thr:
    #                 in_nids_dict[in_nid_key] = link_value['times']
    # for (lnid, rnid), ld_weight in sorted(in_nids_dict.items(), key=lambda x: x[1], reverse=True):
    #     print(lnid, ExtdSLN.Nodes[lnid]._label, '-->', rnid, ExtdSLN.Nodes[rnid]._label, ':', ld_weight)
    #     if type(length_thr) is int and length_thr < len(leaded_nids):
    #         break
    #     if rnid not in leaded_nids:
    #         leaded_nids.append(rnid)
    # ----- Map nodes into sets according to linguistic links -----
    nid2set_dict = {nid: nid for nid in leaded_nids}
    for n1id in leaded_nids:
        for n2id in leaded_nids:
            if n1id == n2id or (n1id, n2id) not in ExtdSLN.adj_matrix:
                continue
            if nid2set_dict[n1id] == nid2set_dict[n2id]:
                continue
            for link in ExtdSLN.adj_matrix[(n1id, n2id)]:
                if link['type'] != 'LEAD':
                    min_setid = min(nid2set_dict[n1id], nid2set_dict[n2id])
                    nid2set_dict[n1id] = min_setid
                    nid2set_dict[n2id] = min_setid
                    break
    for nid in leaded_nids:
        cur_set = nid
        while cur_set != nid2set_dict[cur_set]:
            cur_set = nid2set_dict[cur_set]
        nid2set_dict[nid] = cur_set
    set2nids_dict = {}
    for cur_nid, cur_set in nid2set_dict.items():
        if cur_set in set2nids_dict:
            set2nids_dict[cur_set].append(cur_nid)
        else:
            set2nids_dict[cur_set] = [cur_nid]
    for nids_set in set2nids_dict.values():
        print(nids_set)
        coresln = ThemeSLN([ExtdSLN.Nodes[nid] for nid in nids_set], [], 'core')
        for lnid in nids_set:
            for rnid in nids_set:
                if lnid == rnid:
                    continue
                if (lnid, rnid) in ExtdSLN.adj_matrix:
                    for link_value in ExtdSLN.adj_matrix[(lnid, rnid)]:
                        if link_value['type'] != 'LEAD':
                            templink = ThemeLink(link_value['label'], link_value['type'], link_value["level"],
                                                 ExtdSLN.Nodes[lnid], ExtdSLN.Nodes[rnid], link_value["times"])
                            coresln.Links.append(templink)
        extdSLNs.append(coresln)
        # coresln.showNodes()
        # coresln.showLinks()
        for cur_tuple in GetLabelGenreTuples(coresln, True, _tab):
            if cur_tuple in objVecs:
                extdVecs[cur_tuple] = objVecs[cur_tuple]
            elif cur_tuple in srcVecs:
                extdVecs[cur_tuple] = srcVecs[cur_tuple]
            else:
                extdVecs[cur_tuple] = None
    return extdSLNs, extdVecs


#######################################################################################
# -------------------------- Extend Object SLNs by Lead Routes ---------------------- #
#######################################################################################
# ---- bellman_ford: find the lowest cost no cycle paths and put penalty on longer paths ----
# Input:
#   1. graph: a dict that stores the graph, like {a:{b:-1,c:4}, b:{c:3, d:2, e:2}, c:{}, d:{b:1, c:5}, e: {d: 3}}
#   2. s_nid: the ID of the start node, like 'a' in above example.
#   3. pen_func: means the penalty function, default as _pen which is written in ProcessFiles.py
# Notice: if you want to get the highest cost paths without cycles, change all edge weights into opposites in graph
def bellman_ford(graph, s_nid, pen_func=lambda x: 1, itertime=None):
    if itertime is None:
        itertime = len(graph)-1
    # ---- initiate costs and routes ----
    cost, route = {}, {}
    for nid in graph:
        cost[nid], route[nid] = float('Inf'), [nid]
    cost[s_nid] = 0
    # ---- find routes for each pair of nodes ----
    for i in range(itertime):
        for from_nid in graph:
            for to_nid in graph[from_nid]:
                cur_route = route[from_nid].copy() + [to_nid]
                # -- skip route that contains cycle --
                if len(set(cur_route)) != len(cur_route):
                    continue
                # -- get the cost for current route, pace refers the number of links in the cur_route --
                pace = len(cur_route)-1
                pen_cost = (cost[from_nid] * (pace-1) + graph[from_nid][to_nid] * pen_func(pace-1)) / pace
                if cost[to_nid] > pen_cost:
                    cost[to_nid], route[to_nid] = pen_cost, cur_route
    # ---- pop cost and route for isolated nodes ----
    for nid in graph:
        if cost.get(nid) == float('Inf') or len(route[nid]) == 1:
            cost.pop(nid)
            route.pop(nid)
    return cost, route


def GetLdGraph(leadSLN):
    # ---- initiate lead graph dict ----
    ld_graph = {}
    for node in leadSLN.Nodes:
        ld_graph[node.nid] = {}
    # ---- add lead links into lead graph dict ----
    for link in leadSLN.Links:
        if link._type == 'LEAD':
            ld_graph[link.l_node.nid][link.r_node.nid] = link.times
    return ld_graph


def MakeLdGraphSym(ld_graph):
    sym_ld_graph = {lnid: {rnid: 0.0 for rnid in ld_graph} for lnid in ld_graph}
    for lnid in ld_graph:
        for rnid in ld_graph[lnid]:
            sym_ld_graph[lnid][rnid] += ld_graph[lnid][rnid]
            sym_ld_graph[rnid][lnid] += ld_graph[lnid][rnid]
    return sym_ld_graph


def AlterLinkWeight(ld_graph, _func=np.negative):
    for lnid in ld_graph:
        for rnid in ld_graph[lnid]:
            ld_graph[lnid][rnid] = _func(ld_graph[lnid][rnid])
    return ld_graph


def TransposeGraphDict(ld_graph):
    invert_ld_graph = {lnid: {} for lnid in ld_graph}
    for lnid in ld_graph:
        for rnid in ld_graph[lnid]:
            invert_ld_graph[rnid][lnid] = ld_graph[lnid][rnid]
    return invert_ld_graph


# ---- GetPnum: get the number of paragraphs in the source text ----
def GetPnum(srcfp):
    srcfp_list = GetFileDirPaths(srcfp, depth=3)[0]
    pnum = 0
    for fp in srcfp_list:
        # ----- Check the type of the File -----
        (ftype_prefix, ftype) = os.path.splitext(fp)
        while ftype not in ['.txt', '.xml', '.html', '.xhtml', '']:
            (ftype_prefix, ftype) = os.path.splitext(ftype_prefix)
        if ftype is '':
            continue
        # ----- Process File to get its average sentence number within a paragraph -----
        fstring = ReadFile(fp)
        if ftype == '.txt':
            pnum += len(re.split(r'\*~\*#\*~\*', re.sub(r'(\r\n){2,}|(\n){2,}', '*~*#*~*', fstring)))
        else:
            parser_type = 'lxml-xml' if ftype == '.xml' else 'lxml'
            soup = BeautifulSoup(fstring, parser_type)
            ptags = soup.find_all("p")
            if not ptags:
                texttag = soup.find("text")
                if texttag is not None:
                    text_str = texttag.string.strip()
                    pnum += len(re.split("\n+ {3,}", text_str))
            else:
                pnum += sum([1 if isinstance(ptag.string, str) and ptag.string.strip() else 0 for ptag in ptags])
    return pnum


# ---- Rank all nodes in the source text according to the their lead degree which are calculated by lead routes ----
# Input:
#   1. srcfp: the file path of the source text.
#   2. pkdir: the directory for pickle files which stores the intermediate results.
#   3. ObjSLN: the object SLN whose nodes are served as seed nodes.
#   4. ObjVecs: the dict which stores the embedding vectors for the nodes and links in ObjSLN.
#   5. nsim_thr: the threshold for node vectors' cosine similarity to find the most similar nodes in SrcSLN to seeds.
#   6. objtype: "title" or "query", refers the type of the object SLN.
def RankSrcNodesByLdRoute(srcfp, pkdir, ObjSLN, objVecs={}, simtype="mix", nsim_thr=0.9, _tab=""):
    nrank_pkfp = os.path.join(pkdir, '.'.join([os.path.basename(srcfp), 'NodeRanks', ObjSLN.type, 'pk']))
    if os.path.isfile(nrank_pkfp):
        return Loadpickle(nrank_pkfp)
    # ---- Initiate ldSrcSLN ----
    ldSrcSLN = GetFileCacheDatas(srcfp, 'LeadSrcSLN', pkdir, _tab=_tab)
    # ----- map object SLN's node into source SLN's node, to find the seed nodes in SrcSLN -----
    srcVecs = GetFileCacheDatas(srcfp, "srcVecs", pkdir, _tab=_tab)
    obj2src_map = FindSameNodes(ObjSLN, ldSrcSLN, simtype, nsim_thr, objVecs, srcVecs)
    # for onid, (src_node, sim_score) in obj2src_map.items():
    #     print(ObjSLN.Nodes[onid]._label, "-->", src_node._label, ":", sim_score)
    seed_nids= {}
    for (src_node, sim_score) in obj2src_map.values():
        if src_node.nid not in seed_nids or seed_nids[src_node.nid] < sim_score:
            seed_nids[src_node.nid] = sim_score
    if not seed_nids:
        print(_tab+'\033[31m%s\033[0m' % "Error! Cannot find similar nodes of ObjSLN within SrcSLN as the seed nodes!")
        return []
    # ----- initiate nid2ld_dict which maps each SrcSLN node-ID to lead-degree and lead-route ----
    nid2ld_dict = {node.nid: {"ld-degree": 0.0, "ld-route": []} for node in ldSrcSLN.Nodes}
    for nid in seed_nids:
        nid2ld_dict[nid] = {"ld-degree": 1.0, "ld-route": [[nid]]}
    # ----- Get lead graph dict from ldSrcSLN ------
    ld_graph = GetLdGraph(ldSrcSLN)
    ld_graph = AlterLinkWeight(ld_graph)
    # ----- Get Penalty function in lead route cost calculation -----
    delta, snum, pnum = 1.0, len(GetFileCacheDatas(srcfp, "Sents", pkdir, _tab=_tab)), GetPnum(srcfp)
    if snum > pnum > 0:
        delta = snum / pnum
    # print(_tab + "Average number of sentences within a paragraph:", delta)
    pen_func = lambda x: _pen(x, delta)
    # -- Forward lead-route discovery --
    for (s_nid, sim_score) in seed_nids.items():
        cost, route = bellman_ford(ld_graph, s_nid, pen_func)
        for e_nid in cost:
            # print(s_nid, "->", e_nid, "lead-strength:", np.negative(round(cost[e_nid], 6)), "route:", route[e_nid])
            cur_cost = np.negative(cost[e_nid]) * sim_score
            if cur_cost > 0:
                nid2ld_dict[e_nid]["ld-degree"] += cur_cost
                nid2ld_dict[e_nid]["ld-route"].append(route[e_nid])
    # -- Backward lead-route discovery --
    ld_graph = TransposeGraphDict(ld_graph)
    for (s_nid, sim_score) in seed_nids.items():
        cost, route = bellman_ford(ld_graph, s_nid, pen_func)
        for e_nid in cost:
            route[e_nid].reverse()
            # print(e_nid, "->", s_nid, "lead-strength:", np.negative(round(cost[e_nid], 6)), "route:", route[e_nid])
            cur_cost = np.negative(cost[e_nid]) * sim_score
            if cur_cost > 0:
                nid2ld_dict[e_nid]["ld-degree"] += cur_cost
                nid2ld_dict[e_nid]["ld-route"].append(route[e_nid])
    # ----- Rank SrcSLN nodes' by lead-degree and node_freq -----
    node_rank_list = []
    for nid, D in nid2ld_dict.items():
        cur_node = ldSrcSLN.Nodes[nid]
        cur_node.ld_routes = D["ld-route"]
        if len(D["ld-route"]) > 1:
            cur_node.ld_degree = D["ld-degree"] / len(D["ld-route"])
        else:
            cur_node.ld_degree = D["ld-degree"]
        node_rank_list.append(cur_node)
    node_rank_list.sort(key=lambda n: n.times, reverse=True)
    node_rank_list.sort(key=lambda n: n.ld_degree, reverse=True)
    Dumppickle(nrank_pkfp, node_rank_list)
    return node_rank_list


# ----- WriteRankNodesTable: write ranked node list into Excel tables -----
def WriteRankNodesTable(node_rank_list, table_fp):
    workbook = xlwt.Workbook(encoding='utf-8')
    worksheet = workbook.add_sheet("Source Node Ranks")
    for col, header in enumerate(["Rank Index", "Node-ID", "Node-label", "lead-degree", "Node-freq", "lead-routes"]):
        worksheet.write(0, col, header, xlwt.easyxf('font: bold on'))
    for row, node in enumerate(node_rank_list):
        worksheet.write(row + 1, 0, row)
        worksheet.write(row + 1, 1, node.nid)
        worksheet.write(row + 1, 2, node._label)
        worksheet.write(row + 1, 3, node.ld_degree)
        worksheet.write(row + 1, 4, node.times)
        route_str = ""
        for r in node.ld_routes:
            route_str = '->'.join(map(lambda x: str(x), r)) + "; "
        worksheet.write(row + 1, 5, route_str)
    workbook.save(table_fp)


def CacheRankNodesForDataset(dataset='acl', ftype='abs', obj_sln='TitSLN', obj_vec='srcVecs', simtype='mix', nsim_thr=0.9):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    # ---- rank nodes in source file by lead-degree ----
    if sumtype == 'p':
        srcfp_list = GetFileDirPaths(src_dir, depth=2)[0]
    else:
        srcfp_list = GetFileDirPaths(src_dir, depth=1)[1]
    for srcfp in srcfp_list:
        if not re.match(fnpt, os.path.basename(srcfp)):
            continue
        ObjSLN = GetFileCacheDatas(srcfp, obj_sln, pk_dir)
        objVecs = GetFileCacheDatas(srcfp, obj_vec, pk_dir)
        if ObjSLN is None or objVecs is None:
            continue
        RankSrcNodesByLdRoute(srcfp, pk_dir, ObjSLN, objVecs, simtype, nsim_thr)
    return


# ---- GetObjSLNsByLeadNodes: Get object SLNs by high lead-degree nodes ----
# Inputs:
#   1. adjM: The adjacent Matrix of the source SLN.
#   2. node_rank_list: the theme nodes list of the source SLN ranked by lead-degree
#   3. n_thr: the up threshold of nodes that can contain in object SLNs.
#   5. omlink_types: a set of link types that should be omitted to link high ranked nodes into objSLNs.
#   4. ex_nids: whether to exclude some nodes from object SLN.
def GetObjSLNsByLdRoute(adjM, node_rank_list, n_thr=100, omlink_types={'LEAD'}, ex_nids=None):
    if not isinstance(ex_nids, Iterable):
        ex_nids = set()
    # ---- Get nodes that will be added into ObjSLN ----
    nid2nodes = {}
    for node in node_rank_list:
        if len(nid2nodes) >= n_thr:
            break
        if node.nid in ex_nids:
            continue
        nid2nodes[node.nid] = node
    # ----- Map nodes into sets according to linguistic links -----
    # -- align each pair of nodes that are linked by a link into the same set --
    nid2set_dict = {nid: nid for nid in nid2nodes}
    for (n1id, n2id) in itertools.product(nid2set_dict, nid2set_dict):
        if n1id == n2id or (n1id, n2id) not in adjM or nid2set_dict[n1id] == nid2set_dict[n2id]:
            continue
        for link in adjM[(n1id, n2id)]:
            if link['type'] not in omlink_types:
                min_setid = min(nid2set_dict[n1id], nid2set_dict[n2id])
                nid2set_dict[n1id], nid2set_dict[n2id] = min_setid, min_setid
                break
    # -- map each node into the root set it belongs to --
    for nid in nid2set_dict:
        cur_set = nid
        while cur_set != nid2set_dict[cur_set]:
            cur_set = nid2set_dict[cur_set]
        nid2set_dict[nid] = cur_set
    # ------ Assign nodes into each set ------
    set2nodes = {}
    for cur_nid, cur_set in nid2set_dict.items():
        if cur_set in set2nodes:
            set2nodes[cur_set].append(nid2nodes[cur_nid])
        else:
            set2nodes[cur_set] = [nid2nodes[cur_nid]]
    # ---- Form each node set into objSLN ----
    objSLNs = []
    for Nodes in set2nodes.values():
        Links = []
        for (n1, n2) in itertools.product(Nodes, Nodes):
            if n1.nid == n2.nid or (n1.nid, n2.nid) not in adjM:
                continue
            for link_info in adjM[(n1.nid, n2.nid)]:
                if link_info['type'] in omlink_types:
                    continue
                link = ThemeLink(link_info['label'], link_info['type'], link_info['level'], n1, n2, link_info['times'])
                Links.append(link)
        objSLNs.append(ThemeSLN(Nodes, Links, type="object"))
    gc.collect()
    return objSLNs


def ReduceObjSLN(ObjSLN, node_rank_list, n_thr):
    Rank2Nid_dict = {}
    for node in ObjSLN.Nodes:
        for rank, temp_node in enumerate(node_rank_list):
            if node == temp_node:
                Rank2Nid_dict[rank] = node.nid
                break
    del_nids = {nid for (rank, nid) in sorted(Rank2Nid_dict.items())[n_thr:]}
    nidx, lidx = 0, 0
    while lidx < len(ObjSLN.Links):
        curlink = ObjSLN.Links[lidx]
        if curlink.l_node.nid in del_nids or curlink.r_node.nid in del_nids:
            ObjSLN.Links.pop(lidx)
        else:
            lidx += 1
    while nidx < len(ObjSLN.Nodes):
        curnode = ObjSLN.Nodes[nidx]
        if curnode.nid in del_nids:
            ObjSLN.Nodes.pop(nidx)
        else:
            nidx += 1
    ObjSLN.ReviseNid()
    ObjSLN.BuildAdjMatrix()
    gc.collect()
    return ObjSLN


# ---- RankObjSLNs: rank objSLNs by both size and core nodes they containing, and merge top objSLNs as final ObjSLN ----
# Inputs:
#   1. objSLNs: a list of object SLNs.
#   2. core_nodes: a list of nodes that we view as core nodes.
#   3. n_thr: the node threshold contianed in the final ObjSLN.
def MergeTopObjSLNs(objSLNs, core_nodes=None, n_thr=30, _tab=""):
    if not isinstance(objSLNs, list) or len(objSLNs) == 0:
        print(_tab + '\033[31m%s\033[0m' % "Error! No objsln contained in the objSLNs!")
    if not isinstance(core_nodes, Iterable):
        core_nodes = set()
    for objsln in objSLNs:
        objsln.avg_nfreq = np.average([onode.times for onode in objsln.Nodes])
        objsln.core_node_num = 0
        for cnode in core_nodes:
            for onode in objsln.Nodes:
                if onode == cnode:
                    objsln.core_node_num += 1
                    break
    # ---- Rank objSLNs by the core nodes they containing ----
    # ---- If the core nodes of two objSLNs are same, rank objSLNs by their size ----
    # ---- If the size of two objSLNs are same, rank objSLNs by their average node frequency ----
    objSLNs.sort(key=lambda objsln: objsln.avg_nfreq, reverse=True)
    objSLNs.sort(key=lambda objsln: len(objsln), reverse=True)
    objSLNs.sort(key=lambda objsln: objsln.core_node_num, reverse=True)
    # for sln in objSLNs:
    #     print("=========================")
    #     sln.showNodes()
    #     sln.showLinks()
    # ---- Merge the top ranked objSLNs as the final ObjSLN ----
    ObjSLN = ThemeSLN([], [], 'object')
    for objsln in objSLNs:
        # print("coreNum:", objsln.core_node_num, "curSize:", len(objsln), "AVGnfreq:", objsln.avg_nfreq)
        ObjSLN.MergeSLN(objsln)
        if len(ObjSLN) > n_thr:
            break
    gc.collect()
    return ObjSLN


def ExtdObjsByLdRoute(srcfp, pkdir, ObjSLN, objVecs, n_thr, _mul=3, no_obj=False, simtype='mix', nsim_thr=0.9, **kwargs):
    _tab = kwargs.get("_tab", "")
    SrcSLN = GetFileCacheDatas(srcfp, "SrcSLN", pkdir, _tab=_tab)
    srcVecs = GetFileCacheDatas(srcfp, "srcVecs", pkdir, _tab=_tab)
    # -- Get Core Nodes ID --
    obj2src_nlabel_map = FindSameNodes(ObjSLN, SrcSLN, simtype, nsim_thr, objVecs, srcVecs)
    core_nodes = [src_node for (src_node, sim_score) in obj2src_nlabel_map.values()]
    ex_nids = None
    if no_obj:
        ex_nids = [node.nid for node in core_nodes]
        core_nodes = None
    # -- Get Node Rank List --
    node_rank_list = RankSrcNodesByLdRoute(srcfp, pkdir, ObjSLN, objVecs, simtype, nsim_thr, _tab=_tab+'\t')
    # -- Extend ObjSLN by lead-route --
    objSLNs = GetObjSLNsByLdRoute(SrcSLN.adj_matrix, node_rank_list, n_thr=n_thr*_mul, ex_nids=ex_nids)
    ObjSLN = MergeTopObjSLNs(objSLNs, core_nodes=core_nodes, n_thr=n_thr, _tab=_tab+'\t')
    if (len(ObjSLN) - n_thr) > int(n_thr/4):
        ObjSLN = ReduceObjSLN(ObjSLN, node_rank_list, n_thr)
    # -- Get objVecs for nodes and links in ObjSLN --
    new_objVecs = {}
    for label_tuple in GetLabelGenreTuples(ObjSLN, _tab=_tab+'\t'):
        if label_tuple in objVecs:
            new_objVecs[label_tuple] = objVecs[label_tuple]
        elif label_tuple in srcVecs:
            new_objVecs[label_tuple] = srcVecs[label_tuple]
        else:
            new_objVecs[label_tuple] = None
    gc.collect()
    return ObjSLN, new_objVecs


def TestExtdObjsByLdRoute(srcfp, pkdir, ObjSLN, objVecs, n_thr, _mul=3, no_obj=False, simtype='mix', nsim_thr=0.9, _tab=""):
    SrcSLN = GetFileCacheDatas(srcfp, "SrcSLN", pkdir, _tab=_tab)
    srcVecs = GetFileCacheDatas(srcfp, "srcVecs", pkdir, _tab=_tab)
    # -- Get Core Nodes ID --
    obj2src_nlabel_map = FindSameNodes(ObjSLN, SrcSLN, simtype, nsim_thr, objVecs, srcVecs)
    core_nodes = [src_node for (src_node, sim_score) in obj2src_nlabel_map.values()]
    ex_nids = None
    if no_obj:
        ex_nids = [node.nid for node in core_nodes]
        core_nodes = None
    # -- Get Node Rank List --
    node_rank_list = RankSrcNodesByLdRoute(srcfp, pkdir, ObjSLN, objVecs, simtype, nsim_thr, _tab=_tab+'\t')
    # -- Extend ObjSLN by lead-route --
    objSLNs = GetObjSLNsByLdRoute(SrcSLN.adj_matrix, node_rank_list, n_thr=n_thr*_mul, ex_nids=ex_nids)
    for objsln in objSLNs:
        objsln.showNodes()
        objsln.showLinks()


#######################################################################################
# --------------------------------- Fidelity Factor --------------------------------- #
#######################################################################################
#  ---- Set Fidelity parameters ----
# 1. obj_sln: A string to suggest the Fidelity object SLN, like 'TitSLN', 'TopNodeSLN' and 'QrySLN'.
# 2. obj_vec: A string to suggest the embeding vectors of the nodes and links in obj_sln, like 'srcVecs'.
# 3. no_obj: whether to exclude the object nodes from the extended ObjSLN
# 4. _mul: the multiple number of nodes within the extended ObjSLN, <= 0 means do not extend the ObjSLN.
# 5. simtype: the type to evaluate the label similarity between nodes or links,
#             should be one in ['jcd', 'bleu', 'emb', 'mix'], default as 'mix'.
# 6. nsim_thr: the threshold for the label similarity between two nodes to judge whether they are same, default as 0.9
# 7. take_freq: whether to take the frequency of nodes and links into consideration in Similarity-Flooding Algorithm
#               to get the similarity Matrix between each pair of nodes, default as False.
# 8. topn: the number of top ranked nodes that serves as the minimum core when obj_sln is 'TopNodeSLN'
# 9. _opts: the options for merge the matched node-pairs into Fidelity values, default as ['avg', 'mid', '0.5']
# 10. _dump: whether to dump the dict of Fidelity values for each summary into a pickle file, default as False
# 11. _tab: the space to control the result output when running the Fidelity function.
FID_kwargs = {'obj_sln': 'TopNodeSLN', 'obj_vec': 'srcVecs', 'no_obj': False, '_mul': 3, 'simtype': 'mix',
              'nsim_thr': 0.9, 'take_freq': False, 'topn': 5, '_opts': ['avg', 'mid', '0.5'], '_dump': True,
              '_stem': True, '_stopw': True, '_tab': ''}


# ==== Fidelity: Calculate the Fidelity of a summary to the certain object ====
# Inputs:
#   1. srcfp: the path of the source file.
#   2. sumfp: the path of the summry file.
#   3. pk_dir: the directory for storing the pickle files.
#   4. **kwargs: other parameters to calculate the fidelity.
def Fidelity(srcfp, sumfp, pk_dir, **kwargs):
    DefKwargs(kwargs, FID_kwargs)

    fid_pkfn = '.'.join([os.path.basename(sumfp), "fidelity", kwargs['obj_sln'].lower().rstrip("sln"), "pk"])
    fid_pkfp = os.path.join(pk_dir, fid_pkfn)
    if os.path.isfile(fid_pkfp):
        return Loadpickle(fid_pkfp)

    ObjSLN = GetFileCacheDatas(srcfp, kwargs['obj_sln'], pk_dir, _tab=kwargs['_tab'])
    objVecs = GetFileCacheDatas(srcfp, kwargs['obj_vec'], pk_dir, _tab=kwargs['_tab'])
    SumSLN = GetFileCacheDatas(sumfp, "SumSLN", pk_dir, _tab=kwargs['_tab'])
    sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pk_dir, _tab=kwargs['_tab'])

    # ----- Extend ObjSLN by top-lead-degree ranked nodes in source files -----
    if type(kwargs['_mul']) in [int, float] and kwargs['_mul'] > 0:
        ObjSLN, objVecs = ExtdObjsByLdRoute(srcfp, pk_dir, ObjSLN, objVecs, len(SumSLN), **kwargs)

    # ---- match nodes in SumSLN to ObjSLN ----
    try:
        nsimM, obj_lab2idx, sum_lab2idx = GetNodeSim(ObjSLN, SumSLN, kwargs['simtype'], objVecs, sumVecs,
                                                     kwargs['take_freq'], _tab=kwargs['_tab']+'\t')
    except Exception as e:
        print("Error!", e)
        return None
    idx2mt_dict = greedy_match_pen(nsimM, delta=1.0, _tab=kwargs['_tab']+'\t')

    # # ---- Show node pair matching result ----
    # ObjSLN.showNodes()
    # ObjSLN.showLinks()
    # obj_idx2lab = {idx: lab for lab, idx in obj_lab2idx.items()}
    # sum_idx2lab = {idx: lab for lab, idx in sum_lab2idx.items()}
    # for sum_idx, (mt_score, obj_idx) in idx2mt_dict.items():
    #     print("Summary Node:", sum_idx2lab[sum_idx], "--%0.2f-->" % mt_score, obj_idx2lab[obj_idx])

    # ---- Merge node-match-pairs as fidelity value dict ----
    fid_vals = {_opt: match_scores(idx2mt_dict, _opt) for _opt in kwargs['_opts']}
    # ---- Dump the fidelity value dict into fidelity pickle file if _dump is true ----
    if kwargs.get('_dump', False):
        Dumppickle(fid_pkfp, fid_vals)
    gc.collect()
    return fid_vals


def CacheFidelityForDataset(dataset='acl', ftype='abs', **kwargs):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    kwargs = DefKwargs(kwargs, FID_kwargs)
    objtype = kwargs['obj_sln'].lower().rstrip('sln')
    fid_pkfp = os.path.join(pk_dir, '_'.join([os.path.basename(sum_dir), 'fidelity', objtype]) + ".pk")
    # ------ Check historical Fidelity_dict ------
    if os.path.isfile(fid_pkfp):
        Fidelity_dict = Loadpickle(fid_pkfp)
    # ---- Calculate fidelity values for each file, and merge all these results into a Fidelity_dict -----
    else:
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        Fidelity_dict, err_sumfn = {}, []
        for srcfp in src_sum_fpalign_dict:
            srcfn = os.path.basename(srcfp)
            for sumfp in src_sum_fpalign_dict[srcfp]:
                sumfn = os.path.basename(sumfp)
                fid_vals = Fidelity(srcfp, sumfp, pk_dir, **kwargs)
                if not isinstance(fid_vals, dict) or not fid_vals:
                    err_sumfn.append(sumfn)
                    fid_vals = {_opt: 0.0 for _opt in kwargs['_opts']}
                if srcfn not in Fidelity_dict:
                    Fidelity_dict[srcfn] = {}
                Fidelity_dict[srcfn][sumfn] = fid_vals
        Dumppickle(fid_pkfp, Fidelity_dict)
        if err_sumfn:
            errtxtfn = '_'.join([dataset.upper(), ftype, objtype, 'errFID.txt'])
            WriteFile(os.path.join(score_dir, errtxtfn), '\n'.join(err_sumfn))
        gc.collect()
    return Fidelity_dict


def WriteDatasetFidelityIntoExcel(dataset='acl', Ftypes=['abs'], score_dir=acl_score_dir):
    kwargs = DefKwargs({}, FID_kwargs)
    # ---- merge Fidelity dicts into one ----
    Fidelity_dict = {}
    for ftype in Ftypes:
        cur_fidelity = CacheFidelityForDataset(dataset, ftype, **kwargs)
        for srcfn, sumfn2vals in cur_fidelity.items():
            if srcfn not in Fidelity_dict:
                Fidelity_dict[srcfn] = sumfn2vals
            else:
                Fidelity_dict[srcfn].update(sumfn2vals)
    # ---- Write Fidelity_dict into an excel table ----
    workbook = xlwt.Workbook(encoding='utf-8')
    for _opt in kwargs.get('_opts', []):
        worksheet = workbook.add_sheet("Fidelity-"+_opt, cell_overwrite_ok=True)
        srcfn_list, sysIDs = sorted(list(Fidelity_dict.keys())), {}
        for row, srcfn in enumerate(srcfn_list):
            worksheet.write(row + 1, 0, srcfn)
            for sumfn, _vals in Fidelity_dict[srcfn].items():
                sysid = sumfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, _vals[_opt])
        worksheet.write(0, 0, "src-file-name", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col+1, header, xlwt.easyxf('font: bold on'))
    objtype = kwargs['obj_sln'].lower().rstrip('sln')
    workbook.save(os.path.join(score_dir, '_'.join([dataset.upper()]+Ftypes+[objtype, "fidelity.xls"])))


#######################################################################################
# ------------------------------- Conciseness Factor -------------------------------- #
#######################################################################################
# ---- Set Conciseness parameters ----
# -- the type of similarity between nodes/links --
# -- whether to take node/link frequency into calculation of the redundancy between sentence --
# -- whether to damping the redundancy of sentence pair according to their location gap --
# -- the threshold of redundancy to decide whether damping the redundancy between sentences --
# -- the option to match_scores --
CC_kwargs = {'simtype': 'mix', 'take_freq': False, '_opts': ['min', 'avg', 'mid'], 'pen_gap': True, 'rdd_thr': 0.7,
             '_dump': False, '_tab': ''}


# ---- Disim: get the dissimilarity between two ThemeSLNs from their node-pair similarity matrix ----
# Inputs:
#   1. sim_matrix: the similarity matrix of node-pairs.
#   2. delta: if delta > 0 means using greedy_match_pen to get nidx2match_dict, else use greedy_match.
#   3. _opt: refer to _opt in func:match_scores, default as 'avg'.
#   4. _damping: the ratio to decay the redundancy score.
#   5. rdd_thr: the threshold of redundancy to decide whether to damping according to sent-gap.
def Disim(sim_matrix, base_axis=0, delta=1.0, _opt="avg", _damping=0, rdd_thr=0, _tab=""):
    if not isinstance(sim_matrix, np.ndarray) or len(sim_matrix.shape) != 2 or len(sim_matrix) == 0:
        print(_tab + '\033[31m%s\033[0m' % 'Error! The type of the input matrix is not correct!')
        return 0.0
    if type(delta) in [int, float] and delta > 0:
        obj2base_nidx2match = greedy_match_pen(sim_matrix, base_axis, delta, _tab=_tab)
        base2obj_nidx2match = greedy_match_pen(sim_matrix, 1 - base_axis, delta, _tab=_tab)
    else:
        obj2base_nidx2match = greedy_match(sim_matrix, base_axis, _tab=_tab)
        base2obj_nidx2match = greedy_match(sim_matrix, 1 - base_axis, _tab=_tab)
    rdd_val = (match_scores(obj2base_nidx2match, _opt) + match_scores(base2obj_nidx2match, _opt)) / 2.0
    if type(_damping) in [int, float] and 0 < _damping < 1 and rdd_val < rdd_thr:
        return 1 - rdd_val * _damping
    else:
        return 1 - rdd_val


def GetSentsNsimM(filepath, pkdir, _sln='sumSLNs', _vec='sumVecs', simtype='mix', take_freq=False, _tab=""):
    sents_simM_pkfp = os.path.join(pkdir, os.path.basename(filepath) + ".sents.nsimM.pk")
    if os.path.isfile(sents_simM_pkfp):
        return Loadpickle(sents_simM_pkfp)
    sentSLNs = GetFileCacheDatas(filepath, _sln, pkdir, _tab=_tab)
    allVecs = GetFileCacheDatas(filepath, _vec, pkdir, _tab=_tab)
    snum = len(sentSLNs)
    sents_simM_dict = {}
    for a_sid in range(snum):
        a_sln = sentSLNs[a_sid]
        for b_sid in range(a_sid + 1, snum):
            b_sln = sentSLNs[b_sid]
            try:
                nsimM, a_lab2idx, b_lab2idx = GetNodeSim(a_sln, b_sln, simtype, allVecs, allVecs, take_freq, _tab=_tab+'\t')
            except:
                print(_tab + '\033[31m%s\033[0m' % 'Error! There is no Nodes in the one of the two ThemeSLN!')
                nsimM, a_lab2idx, b_lab2idx = np.zeros(shape=(0, 0)), {}, {}
            sents_simM_dict[(a_sid, b_sid)] = (nsimM, a_lab2idx, b_lab2idx)
    Dumppickle(sents_simM_pkfp, sents_simM_dict)
    gc.collect()
    return sents_simM_dict


def Conciseness(srcfp, sumfp, pk_dir, **kwargs):
    DefKwargs(kwargs, CC_kwargs)

    # ----- Check historical cached data ------
    cc_pkfn = '.'.join([os.path.basename(sumfp), "concise", 'pen' if kwargs['pen_gap'] else "no-pen", "pk"])
    cc_pkfp = os.path.join(pk_dir, cc_pkfn)
    if os.path.isfile(cc_pkfp):
        return Loadpickle(cc_pkfp)

    sumSLNs = GetFileCacheDatas(sumfp, 'sumSLNs', pk_dir, _tab=kwargs['_tab'])
    snum = len(sumSLNs)
    concise_vals = {_opt: 1.0 for _opt in kwargs['_opts']}
    # ---- if the summary contains no sent or the only sent has no node, the value of concise is default as 1.0 ----
    if snum == 0 or (snum == 1 and not sumSLNs[0].Nodes):
        return concise_vals
    # ---- if the summary just contains one sentence, get the dis-similarity between the nodes ----
    if snum == 1:
        sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pk_dir, _tab=kwargs['_tab'])
        nodenum = len(sumSLNs[0].Nodes)
        nid2disim = {node.nid: (1.0/node.times, node.nid) for node in sumSLNs[0].Nodes}
        for b_nid in range(1, nodenum):
            bn = sumSLNs[0].Nodes[b_nid]
            b_lab, b_rpt, b_vec = bn._label, 1.0/bn.times, sumVecs.get(bn._label, None)
            for a_nid in range(b_nid):
                an = sumSLNs[0].Nodes[a_nid]
                a_lab, a_vec = an._label, sumVecs.get(an._label, None)
                disim = (1 - GetSimValue(a_lab, b_lab, kwargs['simtype'], a_vec, b_vec)) * b_rpt
                if nid2disim[b_nid][0] > disim:
                    nid2disim[b_nid] = (disim, a_nid)
        concise_vals = {_opt: match_scores(nid2disim, _opt) for _opt in kwargs['_opts']}
    # -- if the summary contains more than one sentence --
    else:
        sent_nsimM_dict = GetSentsNsimM(sumfp, pk_dir, simtype=kwargs['simtype'], take_freq=kwargs['take_freq'],
                                        _tab=kwargs['_tab']+"\t")
        pen_func = lambda x: 1
        # ---- get the penalty function on sent-gap based on compress rate ----
        if kwargs['pen_gap']:
            srcSLNs = GetFileCacheDatas(srcfp, 'srcSLNs', pk_dir, _tab=kwargs['_tab'])
            if not srcSLNs:
                pen_func = lambda x: _pen(x, snum - 1)
            else:
                pen_func = lambda x: _pen(x, 2 * math.log(len(srcSLNs), snum))
        # -- get the dis-similarity between the sentences --
        sid2disim = {sid: (1.0, sid) for sid in range(1, snum)}
        for b_sid in range(1, snum):
            if not sumSLNs[b_sid].Nodes:
                continue
            node_rpt = len(sumSLNs[b_sid].Nodes) / sum([bn.times for bn in sumSLNs[b_sid].Nodes])
            for a_sid in range(b_sid):
                nsimM = sent_nsimM_dict[(a_sid, b_sid)][0]
                # -- skip the sent-pair that one contains no sentence or both contain the same single node --
                if len(nsimM) == 0 or (len(nsimM) == 1 and nsimM[0][0] == 1.0):
                    continue
                _disim = Disim(nsimM, _damping=pen_func(b_sid - a_sid - 1), rdd_thr=kwargs['rdd_thr']) * node_rpt
                if _disim < sid2disim[b_sid][0]:
                    sid2disim[b_sid] = (_disim, a_sid)
        # -- Merge all the dis-similarity of sentence-pairs into conciseness dict --
        concise_vals = {_opt: match_scores(sid2disim, _opt) for _opt in kwargs['_opts']}
    # ---- Dump the conciseness value dict into pickle file if _dump is true ----
    if kwargs.get('_dump', False):
        Dumppickle(cc_pkfp, concise_vals)
    gc.collect()
    return concise_vals


def CacheConcisenessForDataset(dataset='acl', ftype='abs'):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    kwargs = DefKwargs({}, CC_kwargs)

    # ------ Check historical Fidelity_dict ------
    concise_pkfn = '_'.join([os.path.basename(sum_dir), 'concise', 'pen' if kwargs['pen_gap'] else 'no-pen']) + '.pk'
    concise_pkfp = os.path.join(pk_dir, concise_pkfn)
    if os.path.isfile(concise_pkfp):
        return Loadpickle(concise_pkfp)

    # ---- Calculate fidelity values for each file, and merge all these results into a Fidelity_dict -----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    Concise_dict, err_sumfn = {}, []
    for srcfp in src_sum_fpalign_dict:
        srcfn = os.path.basename(srcfp)
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sumfn = os.path.basename(sumfp)
            concise_vals = Conciseness(srcfp, sumfp, pk_dir, **kwargs)
            if not isinstance(concise_vals, dict) or not concise_vals:
                err_sumfn.append(sumfn)
                concise_vals = {_opt: 0.0 for _opt in kwargs['_opts']}
            if srcfn not in Concise_dict:
                Concise_dict[srcfn] = {}
            Concise_dict[srcfn][sumfn] = concise_vals
    Dumppickle(concise_pkfp, Concise_dict)
    if err_sumfn:
        WriteFile(os.path.join(score_dir, '_'.join([dataset.upper(), ftype, 'errCC.txt'])), '\n'.join(err_sumfn))
    gc.collect()
    return Concise_dict


#######################################################################################
# -------------------------- Add lead links into SumSLN ----------------------------- #
#######################################################################################
def BuildLeadSumSLN(srcfp, sumfp, pkdir, simtype='mix', nsim_thr=0.7, ld_ratios=(0.6, 0.4), iter_times=3, route_len=3,
                    _tab="", **kwargs):
    ldSumSLN_pkfp = os.path.join(pkdir, os.path.basename(sumfp) + '.LeadSumSLN.pk')
    # ---- If the lead_sum_SLN has been built before, just load and return it ----
    if os.path.isfile(ldSumSLN_pkfp):
        return Loadpickle(ldSumSLN_pkfp)

    # ---- Initiate the basic lead_summary_SLN ----
    lead_SumSLN = GetFileCacheDatas(sumfp, dtype='SumSLN', pkfile_dir=pkdir, _tab=_tab)
    lead_SumSLN.type = 'leadsum'

    # ---- Map the sumSLN node with its most similar srcSLN node ----
    ldSrcSLN = GetFileCacheDatas(srcfp, dtype='LeadSrcSLN', pkfile_dir=pkdir, _tab=_tab)
    srcVecs = GetFileCacheDatas(srcfp, dtype='srcVecs', pkfile_dir=pkdir, _tab=_tab)
    sumVecs = GetFileCacheDatas(sumfp, dtype='sumVecs', pkfile_dir=pkdir, _tab=_tab)
    sum2src_node_map = FindSameNodes(lead_SumSLN, ldSrcSLN, simtype, nsim_thr, sumVecs, srcVecs)
    nfreq_thr = np.median([node.times for node in ldSrcSLN.Nodes])

    # ---- Add direct lead links into lead_SumSLN ----
    lead_info_list = GetLeadPKForSrcFile(srcfp, pkdir, lead_scope=len(ld_ratios), _tab=_tab + "\t")
    lead_SumSLN = AddLeadLinks(lead_SumSLN, lead_info_list, sum2src_node_map, nfreq_thr, ld_ratios, _tab)

    # ---- Add lead links that are formed by lead-route in ldSrcSLN ----
    # -- get lead graph of the SrcSLN --
    ld_graph = AlterLinkWeight(GetLdGraph(ldSrcSLN))
    # -- call bellman_ford algorithm to find lead-routes --
    pen_func = lambda x: _pen(x, 1.0)
    ld_route_dict = {}
    for n1id, (na, nasim) in sum2src_node_map.items():
        cost, route = bellman_ford(ld_graph, na.nid, pen_func, iter_times)
        for n2id, (nb, nbsim) in sum2src_node_map.items():
            if n1id == n2id or nb.nid not in cost:
                continue
            ld_weight = np.negative(cost[nb.nid]) * min(nasim, nbsim)
            if ld_weight > 0:
                ld_route_dict[(n1id, n2id)] = (ld_weight, route[nb.nid])
    # -- update direct lead-link in the lead_SumSLN by higher lead-route-weight --
    for link in lead_SumSLN.Links:
        if link._type != 'LEAD':
            continue
        n1id, n2id = link.l_node.nid, link.r_node.nid
        if (n1id, n2id) in ld_route_dict:
            (cur_lead, cur_route) = ld_route_dict[(n1id, n2id)]
            if cur_lead > link.times and len(cur_route) <= route_len:
                # print(n1id, "->", n2id, "lead-link:", round(link.times, 6), "lead-weight:", round(cur_lead, 6),
                # "route:", cur_route)
                link.times = cur_lead
            ld_route_dict.pop((n1id, n2id))
    # -- add new lead-link into the lead_SumSLN that
    for (n1id, n2id), (cur_lead, cur_route) in ld_route_dict.items():
        if len(cur_route) <= route_len:
            # print(n1id, "->", n2id,  "lead-weight:", round(cur_lead, 6), "route:", cur_route)
            n1, n2 = lead_SumSLN.Nodes[n1id], lead_SumSLN.Nodes[n2id]
            lead_SumSLN.Links.append(ThemeLink("LEAD-TO", 'LEAD', 0, n1, n2, cur_lead))

    lead_SumSLN.adj_matrix = lead_SumSLN.BuildAdjMatrix()

    Dumppickle(ldSumSLN_pkfp, lead_SumSLN)
    return lead_SumSLN


#######################################################################################
# ------- Split the LeadSumSLN into several subSLNs to check its coherence ---------- #
#######################################################################################
def LeadAdjMatrix(leadSLN):
    # ---- make sure that nid for each node in leadSLN is equal to its index ----
    leadSLN.ReviseNid()
    # ---- Initiate the adjacent matrix of lead links ----
    ld_adjM = np.zeros((len(leadSLN.Nodes), len(leadSLN.Nodes)))
    # ---- Add lead link weights into ld_adjM ----
    for link in leadSLN.Links:
        # ---- add weight of current lead link into ld_adjM ----
        if link._type == 'LEAD':
            ld_adjM[link.l_node.nid][link.r_node.nid] += link.times
    return ld_adjM


# ---- LeadCohesion: get the cohesion of lead links within a subSLN's adjacent-matrix of lead links ----
# Input:
#   1. lead_adjM: the adjacent-matrix of lead links, should be a numpy 2D arrays.
def LeadCohesion(lead_adjM):
    if not isinstance(lead_adjM, np.ndarray) or len(lead_adjM.shape) != 2:
        print('\033[31m%s\033[0m' % "Error! The input lead-adjacent matrix is not correct!")
        return 0.0
    row_num = lead_adjM.shape[0]
    max_out_ldweight = max(np.sum(lead_adjM, axis=1))
    if row_num * max_out_ldweight > 0:
        return np.sum(lead_adjM) / (row_num * max_out_ldweight)
    return 0.0


# ---- VoteLDLinks: return the necessary number of voting links to form a subSLN that all its nodes are stable ----
# Input: n_num: the number of all nodes within the subSLN
def VoteLDlinks(n_num):
    if n_num == 0:
        return 0
    if n_num % 4 == 1:
        return int((3 * n_num ** 2 + 14 * n_num - 17) / 16)
    elif n_num % 4 == 2:
        return int((3 * n_num ** 2 + 16 * n_num - 12) / 16)
    elif n_num % 4 == 3:
        return int((3 * n_num ** 2 + 14 * n_num - 21) / 16)
    else:
        return int((3 * n_num ** 2 + 16 * n_num - 16) / 16)


# -------- GetLeadTHRforSubSLN: Get the lead_link_thr for formming subSLNs --------
# Inputs:
#   1. lead_SumSLN: the summary SLN which contains the lead links between nodes.
#   2. stable_slices: a list that each element means the percentage of nodes switching to stable.
#   3. vote_slices: a list that each element means the percentage of stable nodes that are switched by voting links.
def GetLeadTHRforSubSLN(lead_SumSLN, stable_slices=np.arange(0.25, 1.01, 0.25), vote_slices=np.arange(0.0, 1.01, 0.25), _tab=''):
    n_num = len(lead_SumSLN.Nodes)
    # ---- Rank the lead links reversely by their weights ----
    ld_weights_list = sorted([ld_link.times for ld_link in lead_SumSLN.Links if ld_link._type == 'LEAD'], reverse=True)
    # ---- If current lead_SumSLN contains no node or contains no lead links, return 0.0 ----
    if n_num == 0 or len(ld_weights_list) == 0:
        print(_tab + '\033[31m%s\033[0m' % "Error! No nodes or no lead links in current LeadSumSLN!")
        return 0.0
    # ---- the sv2ld_dict maps (stable_node_proportion, vote_stable_proportion) to number of necessary lead links ----
    sv2ld_dict = {}
    for srate in stable_slices:
        Sn_num = np.round((n_num - 1) * srate) + 1  # number of stable nodes in the subSLN
        Pn_num = n_num - Sn_num  # number of pending nodes in the subSLN
        for vrate in vote_slices:
            vn_num = np.round((Sn_num - 1) * vrate)  # number of stable nodes that are switched by voting links
            bn_num = Sn_num - 1 - vn_num  # number of stable nodes that are switched by back links
            l_num = 2 * bn_num + VoteLDlinks(vn_num + 1) + Pn_num
            sv2ld_dict[(srate, vrate)] = int(l_num)
    ld_thr_idx = len(ld_weights_list)
    for lvl in sorted(set(sv2ld_dict.values()), reverse=True):
        if len(ld_weights_list) >= lvl:
            ld_thr_idx = lvl
            break
    # ---- if the index for the ld_thr is larger than the ld_weights_list, return 0.0 ----
    ld_thr = ld_weights_list[ld_thr_idx-1]
    # print("node-num:", n_num)
    # print("lead link-num:", len(ld_weights_list))
    # print("lead_levels: (stable_rate, vote_rate) -> lead_link_num")
    # for key, val in sv2ld_dict.items():
    #     print("\t", key, '->', val)
    # print("lead_levels:", sorted(set(sv2ld_dict.values()), reverse=True))
    # print("index_selected:", ld_thr_idx)
    # print("ld_thr:", ld_thr)
    return ld_thr


# ---- SubSLNDiscovery: Get the sub-SLNs list from the lead_summary_SLN ----
def SubSLNDiscovery(lead_SumSLN):
    # ==== get lead adjacent matrix ====
    ld_adjM = LeadAdjMatrix(lead_SumSLN)
    # ==== get the threshold of lead weight to separate lead_SumSLN into subSLNs ====
    ldthr = GetLeadTHRforSubSLN(lead_SumSLN)

    subsNodes = []
    Nid2SubIdx = {node.nid: {'STABLE': [], 'PEND': []} for node in lead_SumSLN.Nodes}
    BLANK = lead_SumSLN.Nodes.copy()
    # ==== process each BLANK node ====
    while len(BLANK) > 0:
        # -- initiate the first node as the stable node of a new sub-SLN --
        base_snode = BLANK.pop(0)
        CurBLANK = lead_SumSLN.Nodes.copy()
        CurBLANK.pop(base_snode.nid)
        STABLE, PEND, bidx = [base_snode], [], 0
        # -- convert the blank node linked to this stable node to pending nodes --
        while bidx < len(CurBLANK):
            # -- if the current blank node is led by base_stable_node, add the blank node into the PEND list --
            if ld_adjM[base_snode.nid][CurBLANK[bidx].nid] >= ldthr > 0:
                new_pnode = CurBLANK.pop(bidx)
                PEND.append(new_pnode)
            else:
                bidx += 1
        # -- check each pending node to determine whether it can be convert to a stable node --
        pidx = 0
        while pidx < len(PEND):
            pnode, switch_flag = PEND[pidx], False
            # -- If the pending node points to a stable node, switch_flag turns to TRUE --
            for snode in STABLE:
                if ld_adjM[pnode.nid][snode.nid] >= ldthr > 0:
                    switch_flag = True
                    break
            # -- If the pending node points to half pending nodes, switch_flag turns to TRUE --
            if not switch_flag and len(PEND) >= len(STABLE):
                linked_pnum = 0
                for nxt_pnode in PEND:
                    if ld_adjM[pnode.nid][nxt_pnode.nid] >= ldthr > 0:
                        linked_pnum += 1
                if linked_pnum >= len(PEND) / 2:
                    switch_flag = True
            # -- If half stable nodes point to the pending node, switch_flag turns to TRUE --
            if not switch_flag and len(PEND) <= len(STABLE):
                linked_snum = 0
                for pre_snode in STABLE:
                    if ld_adjM[pre_snode.nid][pnode.nid] >= ldthr > 0:
                        linked_snum += 1
                if linked_snum >= len(STABLE) / 2:
                    switch_flag = True
            # -- If switch_flag is TRUE, convert the pending node into stable node, and all the blank nodes --
            # -- linked by this pending node will be turn into new pending nodes --
            if switch_flag:
                new_snode, bidx = PEND.pop(pidx), 0
                STABLE.append(new_snode)
                while bidx < len(CurBLANK):
                    # -- if the current blank node is led by stable link, add the blank node into the PEND list --
                    if ld_adjM[new_snode.nid][CurBLANK[bidx].nid] >= ldthr > 0:
                        new_pnode = CurBLANK.pop(bidx)
                        PEND.append(new_pnode)
                    else:
                        bidx += 1
            else:
                pidx += 1
        # ---- Process the stable nodes and pending nodes ----
        # -- 1. remove stable nodes and pending nodes from the BLANK ----
        stable_nids = set([snode.nid for snode in STABLE])
        pend_nids = set([pnode.nid for pnode in PEND])
        bidx = 0
        while bidx < len(BLANK):
            if BLANK[bidx].nid in stable_nids or BLANK[bidx].nid in pend_nids:
                BLANK.pop(bidx)
            else:
                bidx += 1
        # -- 2. add stable node into Nid2SubIdx --
        for snid in stable_nids:
            Nid2SubIdx[snid]['STABLE'].append(len(subsNodes))
        # -- 3. check whether the pending node linked to some blank nodes, if so, release it as a blank node --
        pre_PEND = PEND.copy()
        PEND, New_BLANK = [], []
        for pnode in pre_PEND:
            release_flag = False
            for bnode in BLANK:
                if ld_adjM[pnode.nid][bnode.nid] >= ldthr > 0:
                    release_flag = True
                    break
            if not release_flag:
                PEND.append(pnode)
            elif not Nid2SubIdx[pnode.nid]['STABLE'] and not Nid2SubIdx[pnode.nid]['PEND']:
                New_BLANK.append(pnode)
        if New_BLANK:
            BLANK.extend(New_BLANK)
            BLANK.sort(key=lambda node: node.nid)
        # -- 4. add pending nodes into Nid2SubIdx --
        for pnode in PEND:
            Nid2SubIdx[pnode.nid]['PEND'].append(len(subsNodes))
        # ---- Append STABLE and PEND as a sub-SLN ----
        subsNodes.append([STABLE, PEND])

    # ==== Find Controversial Nodes ====
    cnt_stable_nodes, cnt_pend_nodes = [], []
    for node in lead_SumSLN.Nodes.copy():
        if len(Nid2SubIdx[node.nid]['STABLE']) > 1:
            cnt_stable_nodes.append(node)
        if len(Nid2SubIdx[node.nid]['PEND']) > 1:
            cnt_pend_nodes.append(node)
    cnt_nids = set([node.nid for node in cnt_stable_nodes]) | set([node.nid for node in cnt_pend_nodes])

    # ==== Delete Controversial Nodes from each subsNodes ====
    for subidx, [pre_STABLE, pre_PEND] in enumerate(subsNodes):
        STABLE, PEND = [], []
        for node in pre_STABLE:
            if node.nid not in cnt_nids:
                STABLE.append(node)
        for node in pre_PEND:
            if node.nid not in cnt_nids:
                PEND.append(node)
        subsNodes[subidx] = [STABLE, PEND]

    # ==== Add each controversial node into the most suitable sub-SLN ====
    # ---- select a subSLN for each controversial stable nodes that has the maximum cohesion after added the node ----
    for node in cnt_stable_nodes:
        max_cohesion, max_subidx, all_subidxs = 0.0, None, Nid2SubIdx[node.nid]['STABLE']
        for subidx in all_subidxs:
            [STABLE, PEND] = subsNodes[subidx]
            all_nids = sorted(list(set([node.nid for node in STABLE + PEND]) | {node.nid}))
            sub_ld_adjM = ld_adjM[all_nids][:, all_nids]
            temp_cohesion = LeadCohesion(sub_ld_adjM)
            if temp_cohesion > max_cohesion:
                max_cohesion = temp_cohesion
                max_subidx = subidx
        if max_subidx is not None:
            subsNodes[max_subidx][0].append(node)
            cnt_nids.remove(node.nid)
    # ---- select a subSLN for each controversial pending nodes that has the maximum cohesion after added the node ----
    for node in cnt_pend_nodes:
        if node.nid not in cnt_nids:
            continue
        max_cohesion, max_subidx, all_subidxs = 0.0, None, Nid2SubIdx[node.nid]['PEND']
        for subidx in all_subidxs:
            [STABLE, PEND] = subsNodes[subidx]
            all_nids = sorted(list(set([node.nid for node in STABLE + PEND]) | {node.nid}))
            sub_ld_adjM = ld_adjM[all_nids][:, all_nids]
            temp_cohesion = LeadCohesion(sub_ld_adjM)
            if temp_cohesion > max_cohesion:
                max_cohesion = temp_cohesion
                max_subidx = subidx
        if max_subidx is not None:
            subsNodes[max_subidx][1].append(node)
            cnt_nids.remove(node.nid)
    # ---- process nodes that cannot be process by previous step, this kinds of nodes exist because ----
    # ---- their suitable subSLN has already be clear when deleting all the controversial nodes ----
    cnt_nid2sp_dict = {nid: 1 for nid in cnt_nids}
    for node in cnt_stable_nodes:
        if node.nid in cnt_nid2sp_dict:
            cnt_nid2sp_dict[node.nid] = 0
    for nid in cnt_nids:
        node = lead_SumSLN.Nodes[nid]
        all_subidxs = list(set(Nid2SubIdx[nid]['STABLE'] + Nid2SubIdx[nid]['PEND']))
        max_cohesion = 0.0
        max_subidx = all_subidxs[0]  # add it into the first one if all its subSLNs are empty
        for subidx in all_subidxs:
            [STABLE, PEND] = subsNodes[subidx]
            all_nids = sorted(list(set([node.nid for node in STABLE + PEND]) | {node.nid}))
            sub_ld_adjM = ld_adjM[all_nids][:, all_nids]
            temp_cohesion = LeadCohesion(sub_ld_adjM)
            if temp_cohesion > max_cohesion:
                max_cohesion = temp_cohesion
                max_subidx = subidx
        subsNodes[max_subidx][cnt_nid2sp_dict[node.nid]].append(node)
    # ---- delete empty subSLN, and add links into the subSLN ----
    subSLNs = []
    for [STABLE, PEND] in subsNodes:
        # -- skip the cases that subsNodes contains no node --
        if not STABLE and not PEND:
            continue
        # -- use level to show the state of node: 0 -> stable, 1 -> pending --
        for snode in STABLE:
            snode.level = 0
        for pnode in PEND:
            pnode.level = 1
        Nodes = sorted(STABLE + PEND, key=lambda node: node.nid)
        # -- get links for current subSLN --
        Links = []
        for (ln, rn) in itertools.product(Nodes, Nodes):
            if ln.nid == rn.nid or (ln.nid, rn.nid) not in lead_SumSLN.adj_matrix:
                continue
            for info in lead_SumSLN.adj_matrix[(ln.nid, rn.nid)]:
                Links.append(ThemeLink(info['label'], info['type'], 0, ln, rn, info['times']))
        subSLNs.append(ThemeSLN(Nodes, Links, type='subsln'))
    return subSLNs


#######################################################################################
# ------------------------------- Coherence Factor ---------------------------------- #
#######################################################################################
sub_CH_kwargs = {'simtype': 'mix', 'nsim_thr': 0.7, 'ld_ratios': (0.6, 0.4), 'iter_times': 3, 'route_len': 3,
                 '_opts': ['avg'], '_dump': False, '_tab': ''}


def Coherence_subSLNs(srcfp, sumfp, pkdir, **kwargs):
    DefKwargs(kwargs, sub_CH_kwargs)

    # ----- Check historical cached data ------
    ch_pkfn = '_'.join([os.path.basename(sumfp), "coherent"]) + ".pk"
    ch_pkfp = os.path.join(pkdir, ch_pkfn)
    if os.path.isfile(ch_pkfp):
        return Loadpickle(ch_pkfp)

    ldSumSLN = BuildLeadSumSLN(srcfp, sumfp, pkdir, **kwargs)
    sum_size = len(ldSumSLN)
    coherence_vals, idx2info = {_opt: 0.0 for _opt in kwargs['_opts']}, {}
    # ---- If no node contain in the SumSLN ----
    if not sum_size:
        return coherence_vals, idx2info

    # ---- If subSLNs has been built before, just load and return it ----
    sub_pkfp = os.path.join(pkdir, os.path.basename(sumfp) + '.subSLNs.pk')
    if os.path.isfile(sub_pkfp):
        subSLNs = Loadpickle(sub_pkfp)
    else:
        subSLNs = SubSLNDiscovery(ldSumSLN)
        Dumppickle(sub_pkfp, subSLNs)

    if len(subSLNs) == 0:
        return coherence_vals, idx2info

    for subidx, subsln in enumerate(subSLNs):
        nid_outw_maps = {}
        for node in subsln.Nodes:
            nid_outw_maps[node.nid] = 0
        for link in subsln.Links:
            nid_outw_maps[link.l_node.nid] += link.times
        # sym_ld_graph = GetLdGraph(subsln)
        # # sym_ld_graph = MakeLdGraphSym(GetLdGraph(subsln))
        # nid_outw_maps = {nid: sum(sym_ld_graph[nid].values()) for nid in sym_ld_graph}
        _cohesion = 0.0
        if max(nid_outw_maps.values()) > 0:
            _cohesion = sum(nid_outw_maps.values()) / (len(nid_outw_maps) * max(nid_outw_maps.values()))
        idx2info[subidx] = (_cohesion, len(nid_outw_maps))

    # ---- new coherence without compare with coreSLN of source ----
    avg_size = np.average([_info[1] for _info in idx2info.values()])
    node_pct = np.sum([_info[1] for _info in idx2info.values() if _info[1] > avg_size]) / sum_size
    for _opt in kwargs['_opts']:
        coherence_vals[_opt] = match_scores({idx: _info for idx, _info in idx2info.items()}, _opt) * node_pct

    if kwargs['_dump']:
        Dumppickle(ch_pkfp, (coherence_vals, idx2info))

    gc.collect()

    return coherence_vals, idx2info


CH_kwargs = {'simtype': 'mix', 'nsim_thr': 0.7, 'ld_ratios': (0.6, 0.4), '_dump': False, '_tab': '', 'vplink': 1,
             'ldlink': 0, 'simlink': 0, 'K': 3, 'coref_opt': False}


def Coherence_maxvpld(srcfp, sumfp, pkdir, **kwargs):
    DefKwargs(kwargs, CH_kwargs)

    # ----- Check historical cached data ------
    paras = list(map(lambda x: kwargs[x], ['vplink', 'ldlink']))

    # ----- Check historical cached data ------
    ch_pkfp = os.path.join(pkdir, '_'.join([os.path.basename(sumfp), "ch", '_'.join(map(lambda x: str(x), paras))]) + ".pk")
    if os.path.isfile(ch_pkfp):
        return Loadpickle(ch_pkfp)

    # ---- Initiate the basic lead_summary_SLN ----
    SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pkdir)
    if not len(SumSLN):
        return None
    ldSrcSLN = GetFileCacheDatas(srcfp, 'LeadSrcSLN', pkdir, ld_ratios=kwargs['ld_ratios'])
    srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', pkdir)
    sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pkdir)

    nodemap_pkfp = os.path.join(pkdir, os.path.basename(sumfp)+".nodemap.pk")
    if os.path.isfile(nodemap_pkfp):
        sum2src_node_map = Loadpickle(nodemap_pkfp)
    else:
        sum2src_node_map = FindSameNodes(SumSLN, ldSrcSLN, kwargs['simtype'], kwargs['nsim_thr'], sumVecs, srcVecs)
        Dumppickle(nodemap_pkfp, sum2src_node_map)

    linkM = np.zeros((len(SumSLN), len(SumSLN)))

    for aidx, an in enumerate(SumSLN.Nodes):
        for bidx, bn in enumerate(SumSLN.Nodes):
            if aidx == bidx and linkM[aidx][bidx] > 0:
                continue
            if an.nid not in sum2src_node_map or bn.nid not in sum2src_node_map:
                continue
            (xn, axsim), (yn, bysim) = sum2src_node_map[an.nid], sum2src_node_map[bn.nid]
            ldnum, vpnum, xyLset, abLset = 0.0, 0, [], SumSLN.adj_matrix.get((an.nid, bn.nid), [])
            for xyl in ldSrcSLN.adj_matrix.get((xn.nid, yn.nid), []):
                if xyl['type'] == 'LEAD' and aidx < bidx:
                    ldnum += xyl['times']
                else:
                    xyLset.append(xyl)
            for abl in abLset:
                maxlsim, ablvec = 0.0, sumVecs.get((abl['label'], 'link'))
                for xyl in xyLset:
                    xylvec = srcVecs.get((xyl['label'], 'link'))
                    maxlsim = max(maxlsim, GetSimValue(abl['label'], xyl['label'], kwargs['simtype'], ablvec, xylvec))
                vpnum += maxlsim
            linkM[aidx][bidx] = kwargs['vplink'] * vpnum + kwargs['ldlink'] * ldnum
            print((an._label, bn._label), "->", (xn._label, yn._label), "ldsim:"+format(ldnum, ".3f"), "vpsim:"+format(vpnum, ".3f"))
            print(abLset)
            print(xyLset)

    ch_vals = {"coherence": np.sum(linkM)/np.prod(linkM.shape)}

    if kwargs['_dump']:
        Dumppickle(ch_pkfp, ch_vals)

    return ch_vals


def ObtainCoref2Nids(alltxt, thmNodes):
    coref2nids = []
    # ---- map node ID to label and vice versa ----
    nid2nstr, nstr2nid, = {}, {}
    for nidx, node in enumerate(thmNodes):
        nid2nstr[nidx] = node._label
        nstr2nid[node._label] = nidx
    # ---- find co-references by NeuralCoref ----
    coref_model = nlp(alltxt)
    for clust in coref_model._.coref_clusters:
        refstr2nids = {}
        for mention in clust.mentions:
            refstr = node.process_label(nltk.pos_tag(nltk.word_tokenize(mention.text)))
            refstr2nids[refstr] = set()
        coref2nids.append(refstr2nids)
    # ---- map ref to potential node ID set ----
    for nid, nstr in nid2nstr.items():
        for refstr2nids in coref2nids:
            for refstr in refstr2nids.keys():
                if nstr in refstr:
                    refstr2nids[refstr].add(nid)
    # ---- delete overlap node ID in each node ID set ----
    for refstr2nids in coref2nids:
        for refstr, nids in refstr2nids.items():
            for check_nid in list(nids):
                for rest_nid in nids:
                    if check_nid != rest_nid and nid2nstr[check_nid] in nid2nstr[rest_nid]:
                        nids.remove(check_nid)
                        break
    return coref2nids


def Coherence_vpldsim(srcfp, sumfp, pkdir, **kwargs):
    DefKwargs(kwargs, CH_kwargs)
    # ----- Check historical cached data ------
    sumfn = os.path.basename(sumfp)
    paras = list(map(lambda x: str(kwargs[x]), ['vplink', 'ldlink', 'simlink']))
    opt_suffix = ("_coref" if kwargs['coref_opt'] else "")
    ch_pkfp = os.path.join(pkdir, '_'.join([sumfn, "ch", '_'.join(paras)]) + opt_suffix + ".pk")
    if os.path.isfile(ch_pkfp):
        return Loadpickle(ch_pkfp)

    # ---- Initiate the basic lead_summary_SLN ----
    SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pkdir)
    if len(SumSLN) < 2:
        return None
    ldSrcSLN = GetFileCacheDatas(srcfp, 'LeadSrcSLN', pkdir, ld_ratios=kwargs['ld_ratios'])
    srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', pkdir)
    sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pkdir)

    if kwargs['ldlink'] > 0:
        nodemap_pkfp = os.path.join(pkdir, sumfn+".nodemap.pk")
        if os.path.isfile(nodemap_pkfp):
            sum2src_node_map = Loadpickle(nodemap_pkfp)
        else:
            sum2src_node_map = FindSameNodes(SumSLN, ldSrcSLN, kwargs['simtype'], kwargs['nsim_thr'], sumVecs, srcVecs)
            Dumppickle(nodemap_pkfp, sum2src_node_map)
    else:
        sum2src_node_map = {}

    nodenum = len(SumSLN)
    vplinkM = np.zeros((nodenum, nodenum))
    ldlinkM = np.zeros((nodenum, nodenum))
    simlinkM = np.zeros((nodenum, nodenum))

    for aidx, an in enumerate(SumSLN.Nodes):
        for bidx, bn in enumerate(SumSLN.Nodes):
            if aidx == bidx and vplinkM[aidx][bidx] > 0:
                continue
            # ---- count verb/prep links ----
            abLset = SumSLN.adj_matrix.get((an.nid, bn.nid), [])
            vplinkM[aidx][bidx] += len(abLset)
            # print((an._label, bn._label), abLset)
            if aidx != bidx:
                # ---- get lead link weight ----
                if an.nid in sum2src_node_map and bn.nid in sum2src_node_map:
                    (xn, axsim), (yn, bysim) = sum2src_node_map[an.nid], sum2src_node_map[bn.nid]
                    for xyl in ldSrcSLN.adj_matrix.get((xn.nid, yn.nid), []):
                        if xyl['type'] == 'LEAD':
                            ldlinkM[aidx][bidx] += xyl['times']
                            # print("\t->", (xn._label, yn._label), "leadlink:", format(xyl['times'], ".3f"))
                # ---- get similairty link weight ----
                anvec, bnvec = sumVecs.get((an._label, 'node'), None), sumVecs.get((bn._label, 'node'), None)
                abnsim = GetSimValue(an._label, bn._label, kwargs['simtype'], anvec, bnvec)
                simlinkM[aidx][bidx] += abnsim
                # print("\tsimlink:", format(abnsim, ".3f"))

    # ---- find the co-reference nodes in SumSLN ----
    if kwargs['coref_opt']:
        coref_pkfp = os.path.join(pkdir, sumfn + "_coref2nids.pk")
        if os.path.isfile(coref_pkfp):
            coref2nids = Loadpickle(coref_pkfp)
        else:
            sum_sents = GetFileCacheDatas(sumfp, "Sents", ai_pkdir)
            coref2nids = ObtainCoref2Nids(' '.join(sum_sents), SumSLN.Nodes)
            Dumppickle(coref_pkfp, coref2nids)
        # ---- obtain the node IDs for merging ----
        merge_nids = []
        for refstr2nids in coref2nids:
            temp_nidset, flag = set(), False
            for nids in refstr2nids.values():
                temp_nidset.update(nids)
            for idx, prenidset in enumerate(merge_nids):
                if len(prenidset.intersection(temp_nidset)) > 0:
                    flag = True
                    merge_nids[idx].update(temp_nidset)
                    break
            if not flag:
                merge_nids.append(temp_nidset)
        for nids in merge_nids:
            nodenum -= len(nids) - 1

    linkM = vplinkM * kwargs['vplink'] + ldlinkM * kwargs['ldlink'] + simlinkM * kwargs['simlink']
    # kwargs['K'] = kwargs['vplink'] + kwargs['ldlink'] + kwargs['simlink']

    ch_vals = {"coherence": np.sum(linkM) / (kwargs['K'] * (nodenum * (nodenum-1)) / 2)}

    if kwargs['_dump']:
        Dumppickle(ch_pkfp, ch_vals)

    return ch_vals


def CacheCoherenceForDataset(dataset='acl', ftype='abs', **kwargs):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    DefKwargs(kwargs, CH_kwargs)

    # ------ Check historical Coherence dict ------
    parastrs = '_'.join(map(lambda x: str(kwargs[x]), ['vplink', 'ldlink', 'simlink']))
    opt_suffix = ("_coref" if kwargs['coref_opt'] else "")
    ch_pkfp = os.path.join(pk_dir, "_".join([os.path.basename(sum_dir), 'coherence', parastrs]) + opt_suffix + ".pk")
    if os.path.isfile(ch_pkfp):
        return Loadpickle(ch_pkfp)

    # ---- Calculate Coherence values for each file, and merge all these results into a Coherence dict -----
    Coherence_dict, err_sumfn = {}, []
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        srcfn = os.path.basename(srcfp)
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sumfn = os.path.basename(sumfp)
            coherence_vals = Coherence_vpldsim(srcfp, sumfp, pk_dir, **kwargs)
            if not isinstance(coherence_vals, dict) or not coherence_vals:
                err_sumfn.append(sumfn)
                coherence_vals = {"coherence": 0.0}
            if srcfn not in Coherence_dict:
                Coherence_dict[srcfn] = {}
            Coherence_dict[srcfn][sumfn] = coherence_vals

    Dumppickle(ch_pkfp, Coherence_dict)

    if err_sumfn:
        WriteFile(os.path.join(score_dir, '_'.join([dataset.upper(), ftype, 'errCH.txt'])), '\n'.join(err_sumfn))

    return Coherence_dict


def WriteDatasetCoherenceIntoExcel(dataset='acl', Ftypes=['abs'], score_dir=acl_score_dir, vpldsim=[(1, 0, 0)], coref_opt=False):
    workbook = xlwt.Workbook(encoding='utf-8')
    for (vp, ld, sim) in vpldsim:
        Tname = '_'.join(["VP" if vp else "noVP", "LD" if ld else "noLD", "SIM" if sim else "noSIM"])
        worksheet = workbook.add_sheet(Tname, cell_overwrite_ok=True)
        # ---- merge Fidelity dicts into one ----
        Coherence_dict = {}
        for ftype in Ftypes:
            cur_coherence = CacheCoherenceForDataset(dataset, ftype, vplink=vp, ldlink=ld, simlink=sim, coref_opt=coref_opt)
            for srcfn, sumfn2val in cur_coherence.items():
                if srcfn not in Coherence_dict:
                    Coherence_dict[srcfn] = sumfn2val
                else:
                    Coherence_dict[srcfn].update(sumfn2val)
        # ---- Write Fidelity_dict into an excel table ----
        srcfn_list, sysIDs = sorted(list(Coherence_dict.keys())), {}
        for row, srcfn in enumerate(srcfn_list):
            worksheet.write(row + 1, 0, srcfn)
            for sumfn, _vals in Coherence_dict[srcfn].items():
                sysid = sumfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, _vals["coherence"])
        worksheet.write(0, 0, "SRC-Fname", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col + 1, header, xlwt.easyxf('font: bold on'))
    opt_suffix = ("_coref" if coref_opt else "")
    workbook.save(os.path.join(score_dir, '_'.join([dataset.upper()]+Ftypes) + "_coherence" + opt_suffix + ".xls"))


#######################################################################################
# ---------------------------------- Test function ---------------------------------- #
#######################################################################################
def WriteDatasetSLNIntoExcel(dataset='acl', Ftypes=['abs'], score_dir=acl_score_dir):
    workbook = xlwt.Workbook(encoding='utf-8')
    worksheet = workbook.add_sheet('_'.join(Ftypes), cell_overwrite_ok=True)
    SLNinfo_dict = {}

    for ftype in Ftypes:
        try:
            pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
        except:
            continue
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        for srcfp in src_sum_fpalign_dict:
            srcfn = os.path.basename(srcfp)
            for sumfp in src_sum_fpalign_dict[srcfp]:
                SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pk_dir)
                sysid = os.path.basename(sumfp).split('.')[-1]
                if srcfn not in SLNinfo_dict:
                    SLNinfo_dict[srcfn] = {}
                SLNinfo_dict[srcfn].update({sysid+'-NodeNum': len(SumSLN.Nodes), sysid+'-LinkNum': len(SumSLN.Links)})

    # ---- Write Fidelity_dict into an excel table ----
    srcfn_list, sysIDs = sorted(list(SLNinfo_dict.keys())), {}
    for row, srcfn in enumerate(srcfn_list):
        worksheet.write(row + 1, 0, srcfn)
        for sysid, _val in SLNinfo_dict[srcfn].items():
            if sysid not in sysIDs:
                sysIDs[sysid] = len(sysIDs)
            col = sysIDs[sysid]
            worksheet.write(row + 1, col + 1, _val)
    worksheet.write(0, 0, "SRC-Fname", xlwt.easyxf('font: bold on'))
    for header, col in sysIDs.items():
        worksheet.write(0, col + 1, header, xlwt.easyxf('font: bold on'))
    workbook.save(os.path.join(score_dir, '_'.join([dataset.upper()]+Ftypes) + "_SumSLNInfo.xls"))


def GetSingleFileInfo(dataset, ftype, srcfn, sumfn):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    if sumtype == 'm':
        srcfp_list = GetFileDirPaths(src_dir, depth=2)[1]
    else:
        srcfp_list = GetFileDirPaths(src_dir, depth=2)[0]
    sumfp_list = GetFileDirPaths(sum_dir, depth=2)[0]
    srcfp, sumfp = "", ""
    for tempfp in srcfp_list:
        if os.path.basename(tempfp) == srcfn:
            srcfp = tempfp
            break
    for tempfp in sumfp_list:
        if os.path.basename(tempfp) == sumfn:
            sumfp = tempfp
            break
    return srcfp, sumfp, pk_dir, score_dir


def TestSentGrammar():
    sumfp = r"F:\Programs\Eclipse\ReadabilityRating\ACL-Dataset\Summary_mrk\P14-2069.xhtml.A.30"
    sents_list = GetSentsList(sumfp)
    grammar_dict = SentsGrammarAnalysis(sents_list)
    for sid, sent in enumerate(sents_list):
        print("==============================================")
        print(sent)
        print("grammar-score:", grammar_dict[sid]['score'])
        print("grammar-errors:")
        for err in grammar_dict[sid]['errors']:
            _start = err['offset']
            _end = _start + err['length']
            print(sent[0:_start] + '\033[31m%s\033[0m' % sent[_start:_end] + sent[_end:], end="\t----")
            print('\033[33m%s\033[0m' % err['message'])


def TestMainSents():
    srcfp = r"F:\Programs\Eclipse\ReadabilityRating\ACL-Dataset\SourceFiles_abs\P14-1008.xhtml.A"
    main_sid2sln_dict = GetMainSents(srcfp, acl_pkdir)
    srcSents = GetFileCacheDatas(srcfp, 'Sents', acl_pkdir)
    for sid in main_sid2sln_dict.keys():
        print('s' + str(sid) + ':', srcSents[sid])


def TestMaxCostPathes():
    graph = {'a': {'b': 1, 'c': -4}, 'b': {'c': -3, 'd': -2, 'e': -2}, 'c': {}, 'd': {'b': -1, 'c': -5}, 'e': {'d': 3}}
    cost, route = bellman_ford(graph, 'a', _pen)
    print(cost)
    print(route)


def TestRankSrcNodes(dataset, ftype, srcfn, obj_sln="TitSLN", obj_vec="srcVecs"):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    if sumtype == 'm':
        srcfp_list = GetFileDirPaths(src_dir, depth=2)[1]
    else:
        srcfp_list = GetFileDirPaths(src_dir, depth=2)[0]
    for srcfp in srcfp_list:
        if os.path.basename(srcfp) == srcfn:
            ObjSLN = GetFileCacheDatas(srcfp, obj_sln, pk_dir)
            objVecs = GetFileCacheDatas(srcfp, obj_vec, pk_dir)
            node_rank_list = RankSrcNodesByLdRoute(srcfp, pk_dir, ObjSLN, objVecs)
            WriteRankNodesTable(node_rank_list, os.path.join(score_dir, srcfn + ".NodeRanks.title.xls"))
            return


def TestExtdObjByLdRoute(dataset='ai', ftype='abs', srcfn='S0004370214000538.xml.A', sumfn='S0004370214000538.xml.A.A'):
    try:
        srcfp, sumfp, pk_dir, score_dir = GetSingleFileInfo(dataset, ftype, srcfn, sumfn)
    except:
        return
    print(sumfn, "... ...")
    SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pk_dir)
    sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pk_dir)
    ObjSLN = GetFileCacheDatas(srcfp, 'TitSLN', pk_dir)
    objVecs = GetFileCacheDatas(srcfp, 'srcVecs', pk_dir)
    ObjSLN, objVecs = ExtdObjsByLdRoute(srcfp, pk_dir, ObjSLN, objVecs, len(SumSLN))
    print("+++++++++++ ObjSLN ++++++++++++")
    ObjSLN.showNodes()
    ObjSLN.showLinks()
    # print("ObjNodes:", len(ObjSLN))
    # print("ObjLinks:", len(ObjSLN.Links))
    print("+++++++++++ SumSLN ++++++++++++")
    SumSLN.showNodes()
    SumSLN.showLinks()
    # DrawSLN(ObjSLN)
    # DrawSLN(SumSLN)
    nsimM, obj_lab2idx, sum_lab2idx = GetNodeSim(ObjSLN, SumSLN, 'mix', objVecs, sumVecs, False)
    idx2mt_dict = greedy_match_pen(nsimM, delta=1.0)
    obj_idx2lab = {idx: lab for lab, idx in obj_lab2idx.items()}
    sum_idx2lab = {idx: lab for lab, idx in sum_lab2idx.items()}
    for sum_idx, (mt_score, obj_idx) in idx2mt_dict.items():
        print("Summary Node:", sum_idx2lab[sum_idx], "--%0.2f-->" % mt_score, obj_idx2lab[obj_idx])
    return ObjSLN, objVecs, SumSLN, sumVecs


def TestFidelity(dataset='acl', ftype='abs', srcfn="P14-1008.xhtml.A", sumfn="P14-1008.xhtml.A.A"):
    try:
        srcfp, sumfp, pk_dir, score_dir = GetSingleFileInfo(dataset, ftype, srcfn, sumfn)
    except:
        return
    fidelity_values = Fidelity(srcfp, sumfp, pk_dir)
    for _opt, _val in fidelity_values.items():
        print("Fidelity-"+_opt+":", round(_val, 4))


def TestConcisePenDelta(dataset, ftype):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    sum_compress_dict = {}
    for srcfp in src_sum_fpalign_dict:
        srcSLNs = GetFileCacheDatas(srcfp, 'srcSLNs', pk_dir)
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sumSLNs = GetFileCacheDatas(sumfp, 'sumSLNs', pk_dir)
            sum_compress_dict[os.path.basename(sumfp)] = (len(srcSLNs), len(sumSLNs))
    for sumfn in sum_compress_dict:
        (src_snum, sum_snum) = sum_compress_dict[sumfn]
        delta = 2 * math.log(len(src_snum), len(sum_snum)) if len(sum_snum) > 1 else 1.0
        pen_last = _pen(sum_snum-2, delta)
        print(','.join([sumfn, str(src_snum), str(sum_snum), '.2%'.format(delta), '.4%'.format(pen_last)]))


def TestConciseness(dataset='acl', ftype='abs', srcfn="P14-1008.xhtml.A", sumfn="P14-1008.xhtml.A.A"):
    try:
        srcfp, sumfp, pk_dir, score_dir = GetSingleFileInfo(dataset, ftype, srcfn, sumfn)
    except:
        return
    concise_val = Conciseness(srcfp, sumfp, pk_dir, rdd_thr=1)
    print(os.path.basename(sumfn).split('.')[-1], ":", concise_val)


def TestLeadSumSLN(dataset='acl', ftype='abs', srcfn="P14-1008.xhtml.A", sumfn="P14-1008.xhtml.A.A", _xls=True):
    try:
        srcfp, sumfp, pk_dir, score_dir = GetSingleFileInfo(dataset, ftype, srcfn, sumfn)
    except:
        return
    lead_sum_SLN = BuildLeadSumSLN(srcfp, sumfp, pk_dir)
    if _xls:
        outfname = sumfn + ".ldM.xls"
        WriteAdjMatrix2Excel(lead_sum_SLN, os.path.join(score_dir, outfname))
    return lead_sum_SLN


def TestSubSLNDiscovery(srcfp, sumfp, pkdir, **kwargs):
    kwargs = DefKwargs(kwargs, CH_kwargs)
    ldSumSLN = BuildLeadSumSLN(srcfp, sumfp, pkdir, **kwargs)
    subSLNs = SubSLNDiscovery(ldSumSLN)
    avgnum = len(ldSumSLN)/len(subSLNs)
    MulNSubSLNs = [sub for sub in subSLNs if len(sub) > 1]
    BigSubSLNs = [sub for sub in subSLNs if len(sub) > avgnum]
    # print(len(ldSumSLN), len(subSLNs), avgnum)
    # for subidx, subsln in enumerate(subSLNs):
    #     print("****************", str(subidx), "sub-SLN ****************")
    #     print(idx, len(sub))
    #     subsln.showNodes()
    #     subsln.showLinks()
    subInfoDict = {"SumFname": os.path.basename(sumfp),
                   "NodeNum": len(ldSumSLN),
                   "SubNum": len(subSLNs),
                   "BigSubNum": len(BigSubSLNs),
                   "BigSubNode": sum([len(sub) for sub in BigSubSLNs]) / len(ldSumSLN),
                   "AvgCohesion": sum([LeadCohesion(LeadAdjMatrix(sub)) for sub in MulNSubSLNs]) / len(MulNSubSLNs)
                   # "AvgCohesion": sum([LeadCohesion(LeadAdjMatrix(sub)) for sub in subSLNs]) / len(subSLNs)
                   }
    return subInfoDict


def LeadSumSubSLNsCounts(dataset='acl', Ftypes=['abs']):
    kwargs = DefKwargs({}, CH_kwargs)
    workbook = xlwt.Workbook(encoding='utf-8')
    headers = ["SumFname", "SubNum", "AvgCohesion", "BigSubNum", "BigSubNode"]
    for ftype in Ftypes:
        try:
            pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
        except:
            continue
        sumfn_subInfos = {}
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        for srcfp in src_sum_fpalign_dict:
            for sumfp in src_sum_fpalign_dict[srcfp]:
                sumfn_subInfos[os.path.basename(sumfp)] = TestSubSLNDiscovery(srcfp, sumfp, pk_dir, **kwargs)
        worksheet = workbook.add_sheet(' '.join(["SubSLNs for", dataset.upper(), ftype.upper()]))
        for col, header in enumerate(headers):
            worksheet.write(0, col, header, xlwt.easyxf('font: bold on'))
        for row, (sumfn, subInfos) in enumerate(sumfn_subInfos.items()):
            worksheet.write(row + 1, 0, sumfn)
            for col, item in enumerate(headers[1:]):
                worksheet.write(row + 1, col + 1, sumfn_subInfos[sumfn][item])
    workbook.save(os.path.join(score_dir, "SubSLNs_counts.xls"))


def TestCoherence(dataset, ftype, srcfn, sumfn, **kwargs):
    try:
        srcfp, sumfp, pk_dir, score_dir = GetSingleFileInfo(dataset, ftype, srcfn, sumfn)
    except:
        return
    coherence_vals = Coherence_vpldsim(srcfp, sumfp, pk_dir, **kwargs)
    print(coherence_vals)


def TestCompCorefCoherence():
    srcfn = 'P14-2098.xhtml.A'
    # TestCoherence('acl', 'abs', srcfn, srcfn+'.A', vplink=1.0, ldlink=0.0, simlink=0.0)
    # TestCoherence('acl', 'abs', srcfn, srcfn + '.A', vplink=1.0, ldlink=0.0, simlink=0.0, coref_opt=True)
    # TestCoherence('acl', 'rnd', srcfn, srcfn+'.R', vplink=1.0, ldlink=0.0, simlink=0.0)
    # TestCoherence('acl', 'rnd', srcfn, srcfn + '.R', vplink=1.0, ldlink=0.0, simlink=0.0, coref_opt=True)
    srcfn = 'AP880911-0016.html'
    TestCoherence('duc', 'p100', srcfn, srcfn + '.B', vplink=1, ldlink=0, simlink=0)
    TestCoherence('duc', 'p100', srcfn, srcfn + '.B', vplink=1, ldlink=0, simlink=0, coref_opt=True)
    TestCoherence('duc', 'p100r', srcfn, srcfn + '.R', vplink=1, ldlink=0, simlink=0)
    TestCoherence('duc', 'p100r', srcfn, srcfn + '.R', vplink=1, ldlink=0, simlink=0, coref_opt=True)


def TestMapCorefNodesIntoOne():
    sumfp = "F:\ReadabilityRating\AI-Dataset\Summary_abs\S000437021300043X.xml.A.A"
    sum_sents = GetFileCacheDatas(sumfp, "Sents", ai_pkdir)
    SumSLN = GetFileCacheDatas(sumfp, "SumSLN", ai_pkdir)
    nodenum = len(SumSLN.Nodes)
    coref2nids = ObtainCoref2Nids(' '.join(sum_sents), SumSLN.Nodes)
    for refstr2nids in coref2nids:
        for refstr, nids in refstr2nids.items():
            print(refstr, ":", nids, end="\t")
        print()
    # ---- obtain the node IDs for merging ----
    merge_nids = []
    for refstr2nids in coref2nids:
        temp_nidset, flag = set(), False
        for nids in refstr2nids.values():
            temp_nidset.update(nids)
        for idx, prenidset in enumerate(merge_nids):
            if len(prenidset.intersection(temp_nidset)) > 0:
                flag = True
                merge_nids[idx].update(temp_nidset)
                break
        if not flag:
            merge_nids.append(temp_nidset)
    # ---- Print number of nodes after merging ----
    print("Number of Nodes Before Merge:", nodenum)
    for nids in merge_nids:
        print(nids)
        nodenum -= len(nids) - 1
    print("Number of Nodes After Merge:", nodenum)


def TestLinkNum2Times():
    pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo('duc', 'm100')
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    lnum2times = {i: 0 for i in range(12)}
    for srcfp in src_sum_fpalign_dict:
        for sumfp in src_sum_fpalign_dict[srcfp]:
            SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pk_dir)
            AdjM = SumSLN.adj_matrix
            for n1 in SumSLN.Nodes:
                for n2 in SumSLN.Nodes:
                    if n1.nid == n2.nid:
                        lnum = len(AdjM.get((n1.nid, n2.nid), []))
                    else:
                        lnum = len(AdjM.get((n1.nid, n2.nid), [])) + len(AdjM.get((n2.nid, n1.nid), []))
                    lnum2times[lnum] += 1
    for lnum, times in lnum2times.items():
        print(lnum, ",\t", times)


#######################################################################################
# ---------------------------------- Main function ---------------------------------- #
#######################################################################################
if __name__ == "__main__":
    # print(GetTHRforMainSent())
    # TestMainSents()
    # TestMaxCostPathes()
    # TestRankSrcNodes('acl', 'abs', 'P14-2104.xhtml.A')
    # TestExtdObjByLdRoute('acl', 'abs', 'P14-2104.xhtml.A', 'P14-2104.xhtml.A.A')
    # TestConciseness('duc', 'm100', srcfn='D078', sumfn='D078.M.100.html.19')
    # TestLeadSumSLN('acl', 'abs', 'P14-1008.xhtml.A', 'P14-1008.xhtml.A.A')
    # LeadSumSubSLNsCounts('acl', ['abs', 'sysA', 'wstA'])
    # TestSubSLNDiscovery('acl', 'abs', 'P14-1008.xhtml.A', 'P14-1008.xhtml.A.A')
    # TestMapCorefNodesIntoOne()
    # TestLinkNum2Times()
    for dataset in ['duc']:
        for ftype in ['p100']:
            CacheRankNodesForDataset(dataset, ftype, 'TopNodeSLN', 'srcVecs', 'mix', 0.9)
            # CacheFidelityForDataset(dataset, ftype)
            # CacheCoherenceForDataset(dataset, ftype, vplink=1.0, ldlink=0.0, simlink=0.0)
            # CacheConcisenessForDataset(dataset, ftype)
            # CacheGrammarForDataset(dataset)
    # WriteDatasetFidelityIntoExcel('acl', ['abs', 'sysA', 'wstA'], acl_score_dir)
    # vpldsim, coref_opt = [(1, 0, 0)], True
    # WriteDatasetCoherenceIntoExcel('ai', ['abs', 'rnd'], ai_score_dir, vpldsim=vpldsim, coref_opt=coref_opt)
    # WriteDatasetCoherenceIntoExcel('acl', ['abs', 'rnd'], acl_score_dir, vpldsim=vpldsim, coref_opt=coref_opt)
    # WriteDatasetCoherenceIntoExcel('duc', ['m100', 'm100r'], duc_score_dir, vpldsim=vpldsim, coref_opt=coref_opt)
    # WriteDatasetCoherenceIntoExcel('duc', ['m200', 'm200r'], duc_score_dir, vpldsim=vpldsim, coref_opt=coref_opt)
    # WriteDatasetCoherenceIntoExcel('duc', ['p100', 'p100r'], duc_score_dir, vpldsim=vpldsim, coref_opt=coref_opt)