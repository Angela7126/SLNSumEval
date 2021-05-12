# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
from QualityFactors import *
from BaselineMethods import *


#######################################################################################
# --------------- CMP Fidelity with Baseline methods on ACL/AI dataset -------------- #
#######################################################################################
def GetSumQualsByOpts(sumfn_quals, sumfn, _opts=None):
    _opts = set() if _opts is None else set(_opts)
    if sumfn not in sumfn_quals:
        return None
    quals = sumfn_quals[sumfn]
    val_opts = _opts.intersection(quals.keys())
    if not val_opts:
        return None
    return pd.Series({_opt: quals[_opt] for _opt in val_opts})


def GetAIACLSumPairs(ref_sum_baseline_dict, _opts, srcfnpt, good_fn_suffix, bad_fn_suffix):
    sumpair_cmp_dict = {}
    for reffn, sumfn_baselines in ref_sum_baseline_dict.items():
        mt_groups = re.match(srcfnpt, reffn)
        if not mt_groups:
            print("Error!", "cannot split source filename from", reffn)
            continue
        srcfn = mt_groups[0]
        good_sumfn = srcfn + '.' + good_fn_suffix
        bad_sumfn = srcfn + '.' + bad_fn_suffix
        if good_sumfn not in sumfn_baselines or bad_sumfn not in sumfn_baselines:
            print("Error! Cannot find the GOOD/BAD summary for source file:", srcfn)
            continue
        good_val = GetSumQualsByOpts(sumfn_baselines, good_sumfn, _opts=_opts)
        bad_val = GetSumQualsByOpts(sumfn_baselines, bad_sumfn, _opts=_opts)
        if good_val is None or bad_val is None:
            print("Error! The options is not contained in Quality_dict!")
            continue
        sumpair_cmp_dict[srcfn] = (good_sumfn, bad_sumfn, good_val - bad_val)
    return sumpair_cmp_dict


def GetCommonKeySet(surface_key2val):
    common_keys = None
    for key2val in surface_key2val.values():
        if common_keys is None:
            common_keys = set(key2val)
        else:
            common_keys = common_keys.intersection(key2val)
    return common_keys


# ---- Delete unique source file's summary pairs from CMPresults ----
def DelUniqueInnerKeys(surface_key2val):
    common_keys = GetCommonKeySet(surface_key2val)
    for surkey, key2val in surface_key2val.items():
        unique_keys = set(key2val) - common_keys
        for unikey in unique_keys:
            surface_key2val[surkey].pop(unikey, 'Have No Such Key!')
    return surface_key2val


def GetSumPairPieDatas(CMPresults):
    # ---- check whether sumpairs can be correctly compared by each kind of metric ----
    metric_sumpairs_dict, all_sumpairs = {}, set()
    for srcfn_sumpairs in CMPresults.values():
        for srcfn, (good_sumfn, bad_sumfn, _diff) in srcfn_sumpairs.items():
            all_sumpairs.add((good_sumfn, bad_sumfn))
            for _opt in _diff.index:
                if _opt not in metric_sumpairs_dict:
                    metric_sumpairs_dict[_opt] = set()
                if _diff[_opt] > 0:
                    metric_sumpairs_dict[_opt].add((good_sumfn, bad_sumfn))
    # ---- get the sumpairs data for draw pie figures ----
    # -- summary pairs that cannot be correctly judged by all metrics --
    wrong_sumpairs = all_sumpairs
    for sumpairs in metric_sumpairs_dict.values():
        wrong_sumpairs = wrong_sumpairs - sumpairs
    label2sumpairs = {'Wrong': wrong_sumpairs}
    # -- the summary pairs that can be correct judged by each metric --
    for metric, sumpairs in metric_sumpairs_dict.items():
        label2sumpairs[metric] = sumpairs
    # -- for each subset of metrics that contains more than two metrics --
    for subset in powerset(metric_sumpairs_dict):
        if len(subset) < 2:
            continue
        sumpairs = all_sumpairs
        for metric in subset:
            sumpairs = sumpairs.intersection(metric_sumpairs_dict[metric])
        label2sumpairs['+'.join(subset)] = sumpairs
        for subsubset in powerset(subset):
            if len(subsubset) == 0 or len(subsubset) == len(subset):
                continue
            del_label = '+'.join(subsubset)
            label2sumpairs[del_label] = label2sumpairs[del_label] - sumpairs
    return label2sumpairs


def CheckAIACLSumPairFid(dataset, Ftypes, ref_ftype='con', fid_opts={'avg', 'mid', '0.5'}, rouge_opts={'ROUGE-2-F'},
                         bleu_opts={'BLEU-4'}, srcfnpt=r"^P14-\d{4}\.xhtml", good_suffix='A.A', bad_suffix='A.W'):
    CMPresults = {}
    if fid_opts is not None:
        src_sum_fids = {}
        for ftype in Ftypes:
            cur_fidelity = CacheFidelityForDataset(dataset, ftype)
            for srcfn, sumfn2vals in cur_fidelity.items():
                if srcfn not in src_sum_fids:
                    src_sum_fids[srcfn] = sumfn2vals
                else:
                    src_sum_fids[srcfn].update(sumfn2vals)
        fid_sumpairs = GetAIACLSumPairs(src_sum_fids, fid_opts, srcfnpt, good_suffix, bad_suffix)
        for srcfn, (goodfn, badfn, fid_diff) in fid_sumpairs.items():
            fid_sumpairs[srcfn] = (goodfn, badfn, pd.Series({'Fidelity': sum(fid_diff > 0) > (len(fid_diff) / 2)}))
        CMPresults['Fidelity'] = fid_sumpairs
    if rouge_opts is not None:
        ref_sum_rouges = CallRougeForAIACL(dataset, Ftypes, ref_ftype)
        CMPresults['ROUGE'] = GetAIACLSumPairs(ref_sum_rouges, rouge_opts, srcfnpt, good_suffix, bad_suffix)
    if bleu_opts is not None:
        ref_sum_bleus = CallBleuForAIACL(dataset, Ftypes, ref_ftype)
        CMPresults['BLEU'] = GetAIACLSumPairs(ref_sum_bleus, bleu_opts, srcfnpt, good_suffix, bad_suffix)

    CMPresults = DelUniqueInnerKeys(CMPresults)

    # ---- Draw Pie Figures ----
    label2sumpairs = GetSumPairPieDatas(CMPresults)
    # for label, sumpairs in label2sumpairs.items():
    #     print(label, len(sumpairs))
    id2name = {'A.A': 'Abs', 'A.W': 'Bad', 'A.03': 'Auto(S)', 'A.31': 'Auto(P)', 'A.99': 'Auto(G)', 'A.79': 'Auto(G2)',
               'A.30': 'Auto(G1)'}
    pie_title = dataset.upper()+": "+id2name.get(good_suffix, good_suffix)+' > '+id2name.get(bad_suffix, bad_suffix)
    DrawPie({label: len(sumpairs) for label, sumpairs in label2sumpairs.items()}, pie_title=pie_title)

    return CMPresults


#######################################################################################
# --------------- Read And Align Human Eval Results on DUC dataset ------------------ #
#######################################################################################
# =========== ReadDUCManvals: read the manual evaluation  results of the DUC 2002 dataset =========
# Inputs:
#   1. Dset_idx: the column idx for the Document Set
#   2. type_idx: the column idx for the summary type ('M' means multiple-document and 'P' means single-document)
#   3. base_idx: the column idx for the base TREC document ID
#   4. size_idx: the column idx for the size of the summary
#   5. refID_idx: the column idx for the reference summary's ID
#   6. sysID_idx: the column idx for the system ID that generates this summary
# Outputs: sum2score_dict -- mapping summaries to its manual evaluation scores, contains keys like:
#   1. sum_info_idxs: maps to a dict that contains the column indexes about summary information,
#                     whose keys including ['dset_idx', 'type_idx', 'base_idx', 'size_idx', 'sysID_idx']
#   2. col_name2idx_dict: maps to a dict that maps each score column's name into its index
#   3. col_idx2name_dict: maps to a dict that maps each score column's indexes into its name
#   4. The evaluation score for each summary. The key is summary information tuple
#      (dset, type, base, size, refID, sysID) mappint to a score dict that maps the score_column_index to the value
def ReadDUCManvals(score_fp, dset_idx=0, type_idx=1, base_idx=2, size_idx=3, sysID_idx=8, refID_idx=6):
    # ----- Check Historical Processed manual evaluation results ----
    pkfp = os.path.join(os.path.dirname(score_fp), os.path.basename(score_fp)+".pk")
    if os.path.isfile(pkfp):
        return Loadpickle(pkfp)
    # ----- split the score table content string into non-empty lines -----
    score_rows = DelEmptyString(ReadFile(score_fp).split('\n'))
    # ----- get the number of columns in the last scoring line -----
    colnum = len(score_rows[-1].split())
    # ----- get the names of each column -----
    colnames, last_colname_row = [], 0
    for last_colname_row, row in enumerate(score_rows):
        if len(row.split()) < colnum or row.startswith('|'):
            row = row.strip(' |')
            if not row or row.startswith('#'):
                continue
            colnames.append(re.sub(r" *\(.+\) *", " ", row).strip())
        else:
            break
    # ----- add sum_info_idxs and colnames into sum2score_dict -----
    sum2score_dict = {"sum_info": ('doc-set', 'sum-type', 'base-fname', 'sum-size', 'sys-sumID', 'ref-sumID'),
                      "sum_info_idxs": (dset_idx, type_idx, base_idx, size_idx, sysID_idx, refID_idx),
                      "col_name2idx_dict": {name: idx for idx, name in enumerate(colnames)},
                      "col_idx2name_dict": {idx: name for idx, name in enumerate(colnames)}}
    # ----- Read score lines into sum2score_dict -----
    for idx, row in enumerate(score_rows[last_colname_row:]):
        score_units = row.split()
        if len(score_units) != colnum:
            print("Row", idx + last_colname_row + 1, "Contains less/more units than the max:", colnum)
            continue
        # ---- delete base document id for multi-document summaries ----
        if 0 <= type_idx < colnum and 0 <= base_idx < colnum and score_units[type_idx] == 'M':
            score_units[base_idx] = ''
        # ---- get the key for indexing the summary, and its score dict ----
        info_key, score_dict = tuple(score_units[temp_idx] for temp_idx in sum2score_dict["sum_info_idxs"]), {}
        for temp_idx in range(colnum):
            if temp_idx not in sum2score_dict["sum_info_idxs"]:
                if score_units[temp_idx].isdigit():
                    score_dict[temp_idx] = int(score_units[temp_idx])
                else:
                    try:
                        score_dict[temp_idx] = np.float(score_units[temp_idx])
                    except:
                        score_dict[temp_idx] = score_units[temp_idx]
        sum2score_dict[info_key] = score_dict
        # if info_key not in sum2score_dict:
        #     sum2score_dict[info_key] = [score_dict]
        # else:
        #     sum2score_dict[info_key].append(score_dict)
    Dumppickle(pkfp, sum2score_dict)
    return sum2score_dict


# ---- GetDUCSumInfoKey: process the DUC summary file name into the summary info tuple ----
# The file names are like:
#   1. Single-document summary: D061          . AP880911-0016      .html.   1
#                                 |                 |                       |
#                               document-set  base-document-name        system-ID
#   2. Multi-document summary: D067         . M           . 200          .html.  2
#                                |            |              |                   |
#                              document-set  summary-type   summary-size        system-ID
# The output is a tuple including: (document-set, summary-type, base-document-name, summary-size, system-ID)
def GetDucSumInfoKey(sumfn, ftype='p100'):
    namefrags = sumfn.split('.')
    dset = namefrags[0]
    sumtype = ftype[0].upper()
    basefile = namefrags[1] if sumtype == 'P' else ""
    sumsize = '0' * (3-len(ftype[1:])) + ftype[1:]
    sysID = namefrags[-1]
    return (dset, sumtype, basefile, sumsize, sysID)


# ---- AlignDUCSumFnameWithManVals: check each DUC summary in ftype-dir to find the summaries that has human scores ----
def AlignDUCSumfnWithManvals(ftype):
    # ----- Check Historical Processed manual evaluation results ----
    pkfp = os.path.join(duc_score_dir,  '.'.join([ftype, 'sumfn2manvals', 'pk']))
    if os.path.isfile(pkfp):
        return Loadpickle(pkfp)

    man_sum2score_dict = ReadDUCManvals(os.path.join(duc_score_dir, "manual_results.txt"))
    suminfo_ref_manvals = {}
    for sum_info, man_scores in man_sum2score_dict.items():
        if type(sum_info) is not tuple:
            continue
        suminfo_ref_manvals[sum_info[:5]] = {'refID': sum_info[5], 'man_scores': man_scores}

    pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo('duc', ftype)
    sumfn_ref_manvals = {}
    for sumfp in GetFileDirPaths(sum_dir)[0]:
        sumfn = os.path.basename(sumfp)
        sum_info = GetDucSumInfoKey(sumfn, ftype)
        if sum_info in suminfo_ref_manvals:
            sumfn_ref_manvals[sumfn] = suminfo_ref_manvals[sum_info]

    # for sumfn, ref_manvals in sumfn_ref_manvals.items():
    #     print(sumfn, '\t', ref_manvals['refID'], '\t', ref_manvals['man_scores'])

    Dumppickle(pkfp, (sumfn_ref_manvals, man_sum2score_dict["col_name2idx_dict"]))
    return sumfn_ref_manvals, man_sum2score_dict["col_name2idx_dict"]


def GetDUCManvalQualDicts(ftype='p100', quality_type='fidelity'):
    print("********** Get", quality_type.upper(), "on DUC", ftype.upper(), "**********")
    sumfn_ref_manvals, col_name2idx_dict = AlignDUCSumfnWithManvals(ftype)
    Quality_dict, manval_name2idx, manval_func = {}, {}, None
    if quality_type == 'fidelity':
        Quality_dict = CacheFidelityForDataset('duc', ftype)
        for _name in ['Mean coverage']:  #'Median coverage', 'Mean length-adjusted coverage', 'Median length-adjusted coverage'
            manval_name2idx[_name] = col_name2idx_dict.get(_name)
    elif quality_type == 'concise':
        Quality_dict = CacheConcisenessForDataset('duc', ftype)
        manval_func = lambda x: sum([3 - i for i in x]) / (len(x) * 3)
        manval_name2idx['Q11'] = col_name2idx_dict.get('Q11')
    elif quality_type == 'coherence':
        Quality_dict = CacheCoherenceForDataset('duc', ftype)
        manval_func = lambda x: sum([3 - i for i in x]) / (len(x) * 3)
        for _name in ['Q4', 'Q5', 'Q12']:   # 'Q4', 'Q5', 'Q7', 'Q8', 'Q12'
            manval_name2idx[_name] = col_name2idx_dict.get(_name)
    else:
        print("Quality type should be one in ['fidelity', 'concise', 'coherence']")
        return sumfn_ref_manvals, Quality_dict, manval_name2idx, manval_func
    return sumfn_ref_manvals, Quality_dict, manval_name2idx, manval_func


def GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func):
    sumfn_manvals, manval_names = {}, list(manval_name2idx.keys())
    if manval_func is not None:
        manval_names = ['+'.join(manval_names)]
    for sumfn, ref_manvals in sumfn_ref_manvals.items():
        manvals = {_name: ref_manvals['man_scores'][_idx] for _name, _idx in manval_name2idx.items()}
        if manval_func is not None:
            manvals = {manval_names[0]: manval_func(manvals.values())}
        sumfn_manvals[sumfn] = manvals
    return sumfn_manvals, manval_names


# ---- GetDUCSumfn2RefID: Get the reference summary ID for each of the summary ----
# 2. refopt: the option to choose the reference summary
#            (1) 'same': use the same summary that human experts used to evaluate the summary ...
#            (2) 'all': use all the human written summaries as the references ...
#            (3) 'diff': use the summary that are not used by human experts ...
def GetDUCSumfn2RefID(sumfn_ref_manvals, ftype='p100', refopt='same'):
    if refopt == 'same':
        return {sumfn: ref_manvals['refID'] for sumfn, ref_manvals in sumfn_ref_manvals.items()}
    else:
        # ---- get filename pattern for the references according to the file-type of the dataset ----
        ref_fnpt = duc_std_psnpt if ftype.startswith('p') else duc_std_msnpt
        sumfnlist = GetFileNameList(duc_fsdir[ftype][1])
        basefn2sumfns = {}
        for sumfn in sumfnlist:
            basefn = '.'.join(sumfn.split('.')[:-1])
            if basefn not in basefn2sumfns:
                basefn2sumfns[basefn] = set()
            basefn2sumfns[basefn].add(sumfn)
        # ---- get the summary's expert suggested references ----
        sumfn2refID = {}
        for sumfn, ref_manvals in sumfn_ref_manvals.items():
            refID = ref_manvals['refID']
            sumfn2refID[sumfn] = {refID, } if isinstance(refID, str) else set(refID)
        # ---- check all summaries of the same source text to find all the IDs that can be used as references ----
        for basefn, sumfnset in basefn2sumfns.items():
            all_refIDs = {sumfn.split('.')[-1] for sumfn in sumfnset if re.match(ref_fnpt, sumfn)}
            for sumfn in sumfnset:
                if sumfn not in sumfn2refID:
                    continue
                elif refopt == 'all':
                    sumfn2refID[sumfn] = all_refIDs
                elif refopt == 'diff':
                    sumfn2refID[sumfn] = all_refIDs - sumfn2refID[sumfn]
        # ---- delete summaries that： have not references, or one of its references is itself ----
        for sumfn, refIDset in list(sumfn2refID.items()):
            if not refIDset or sumfn.split('.')[-1] in refIDset:
                del sumfn2refID[sumfn]
        return sumfn2refID


# ==== GetDUCSumfnPairs: return the summary-filename pairs that each pair of summaries: ====
# (1) generated for the same source file
# (2) the first is better than the second judged by human experts.
def GetDUCSumfnPairs(srcfn_sumfnset, sumfn_ref_manvals, manval_name2idx, manval_func):
    if manval_func is None:
        man_sumfnpairs_dict = {_name: set() for _name in manval_name2idx}
    else:
        man_sumfnpairs_dict = {'+'.join(manval_name2idx.keys()): set()}
    for sumfnset in srcfn_sumfnset.values():
        for (a_fn, b_fn) in itertools.product(sumfnset, sumfnset):
            if a_fn != b_fn:
                a_vals = sumfn_ref_manvals[a_fn]['man_scores']
                a_vals = pd.Series({_name: a_vals[_idx] for _name, _idx in manval_name2idx.items()})
                b_vals = sumfn_ref_manvals[b_fn]['man_scores']
                b_vals = pd.Series({_name: b_vals[_idx] for _name, _idx in manval_name2idx.items()})
                if manval_func is not None:
                    a_vals = pd.Series({'+'.join(manval_name2idx.keys()): manval_func(a_vals)})
                    b_vals = pd.Series({'+'.join(manval_name2idx.keys()): manval_func(b_vals)})
                diff_vals = a_vals - b_vals
                for _name in diff_vals.index:
                    if diff_vals[_name] > 0:
                        man_sumfnpairs_dict[_name].add((a_fn, b_fn))
    return man_sumfnpairs_dict


def GetDUCSumPairCMPs(sumfn_quals, sumfnpairs, _opts):
    sumpair_cmp = {}
    for (goodfn, badfn) in sumfnpairs:
        if goodfn not in sumfn_quals or badfn not in sumfn_quals:
            print("Error! Cannot find the GOOD/BAD summary as", (goodfn, badfn))
            continue
        good_val = GetSumQualsByOpts(sumfn_quals, goodfn, _opts=_opts)
        bad_val = GetSumQualsByOpts(sumfn_quals, badfn, _opts=_opts)
        if good_val is None or bad_val is None:
            print("Error! The options is not contained in Quality_dict!")
            continue
        sumpair_cmp[(goodfn, badfn)] = (goodfn, badfn, good_val - bad_val)
    return sumpair_cmp


def GetDUCFnsetsQuals(sumfn_ref_manvals, Quality_dict):
    srcfn_sumfnset, sumfn_quals = {}, {}
    for srcfn, sumfn2quals in Quality_dict.items():
        for sumfn, quals in sumfn2quals.items():
            if sumfn in sumfn_ref_manvals and sumfn not in sumfn_quals:
                sumfn_quals[sumfn] = quals
                if srcfn not in srcfn_sumfnset:
                    srcfn_sumfnset[srcfn] = {sumfn}
                else:
                    srcfn_sumfnset[srcfn].add(sumfn)
    # for srcfn, sumfnset in srcfn_sumfnset.items():
    #     print(srcfn, len(sumfnset))
    #     for sumfn in sumfnset:
    #         print('\t'+sumfn, sumfn_quals[sumfn])
    return srcfn_sumfnset, sumfn_quals


def GetDUCSysID2AvgVals(sumfn_vals, sum_fnpt, adopt_sumfns=None):
    sysID_sumfn_vals, sysID_avgval = {}, {}
    for sumfn in sumfn_vals:
        if not re.match(sum_fnpt, sumfn):
            continue
        if adopt_sumfns is not None and sumfn not in adopt_sumfns:
            continue
        sysID = sumfn.split('.')[-1]
        if sysID not in sysID_sumfn_vals:
            sysID_sumfn_vals[sysID] = {}
        sysID_sumfn_vals[sysID][sumfn] = sumfn_vals[sumfn]
    for sysID, sumfn2vals in sysID_sumfn_vals.items():
        sysID_sumfn_vals[sysID] = pd.DataFrame(sumfn2vals)
        sysID_avgval[sysID] = sysID_sumfn_vals[sysID].mean(axis=1)
    sysID_avgval = pd.DataFrame(sysID_avgval)
    # print("======== Average Value of", sysID_avgval.index.tolist(), "========")
    # for sysID, sumfn2vals in sysID_sumfn_vals.items():
    #     print('---- sysID', sysID, ':', 'total_summary ->', sumfn2vals.shape[1], '----')
    #     for _name in sysID_avgval.index:
    #         print('\tAVG', _name + ":", "{:.6f}".format(sysID_avgval.loc[_name, sysID]))
    #     print("\t*** For each summary: ***")
    #     for sumfn in sumfn2vals.keys():
    #         print("\t\t"+sumfn, dict(sumfn2vals[sumfn]))
    return sysID_sumfn_vals, sysID_avgval


def GetSysID2AvgQual(metric_sumfn2vals, sum_fnpt, adopt_sumfns=None):
    sysID_sumfn_quals, sysID_avgqual = {}, {}
    for metric_num, sumfn2quals in metric_sumfn2vals.items():
        for sumfn, quals in sumfn2quals.items():
            if not re.match(sum_fnpt, sumfn):
                continue
            if adopt_sumfns is not None and sumfn not in adopt_sumfns:
                continue
            sysID = sumfn.split('.')[-1]
            if sysID not in sysID_sumfn_quals:
                sysID_sumfn_quals[sysID] = {}
            if sumfn not in sysID_sumfn_quals[sysID]:
                sysID_sumfn_quals[sysID][sumfn] = {}
            sysID_sumfn_quals[sysID][sumfn].update(quals)
    for sysID, sumfn2quals in sysID_sumfn_quals.items():
        sysID_sumfn_quals[sysID] = pd.DataFrame(sumfn2quals)
        sysID_avgqual[sysID] = sysID_sumfn_quals[sysID].mean(axis=1)
    sysID_avgqual = pd.DataFrame(sysID_avgqual)
    # print("======== Average", quality_type.upper(), "on", sysID_avgqual.index.tolist(), "========")
    # for sysID, sumfn2quals in sysID_sumfn_quals.items():
    #     print('---- sysID', sysID, ':', 'total_summary ->', sumfn2quals.shape[1], '----')
    #     for qual_opt in sysID_avgqual.index:
    #         print('\tAVG', qual_opt + ":", "{:.6f}".format(sysID_avgqual.loc[qual_opt, sysID]))
    #     print("\t*** Quality values for each summary: ***")
    #     for sumfn in sumfn2quals.keys():
    #         print("\t\t"+sumfn, dict(sumfn2quals[sumfn]))
    return sysID_sumfn_quals, sysID_avgqual


#######################################################################################
# ------ CMP Qualities with Human-scores and Baseline-methods on DUC dataset -------- #
#######################################################################################
def DelUnselectOpt(sumfn_quals, select_opts=None):
    for sumfn, quals in sumfn_quals.items():
        for _opt in list(quals.keys()):
            if select_opts is not None and _opt not in select_opts:
                quals.pop(_opt)
    return sumfn_quals


def GetMetricSumfn2Vals(sumfn_ref_manvals, ftype, pyrd_opts=None, rouge_opts=None, bleu_opts=None, jcd_opts=None,
                        nov_opts=None, lolch_opts=None, refopt='same'):
    metric_sumfn2vals = {}
    if rouge_opts is not None:
        kwargs = {'_ngram': 2, '_l': True, '_w': False, '_su4': True, '_stem': True, '_stopw': True}
        sumfn_rouges = CallRougeForDUC(GetDUCSumfn2RefID(sumfn_ref_manvals, ftype, refopt), ftype, refopt, **kwargs)
        DelUnselectOpt(sumfn_rouges, select_opts=rouge_opts)
        metric_sumfn2vals['rouge'] = sumfn_rouges
    if bleu_opts is not None:
        kwargs = {'_ngram': 4, '_stem': True, '_stopw': True}
        sumfn_bleus = CallBleuForDUC(GetDUCSumfn2RefID(sumfn_ref_manvals, ftype, refopt), ftype, refopt, **kwargs)
        DelUnselectOpt(sumfn_bleus, select_opts=bleu_opts)
        metric_sumfn2vals['bleu'] = sumfn_bleus
    if pyrd_opts is not None:
        kwargs = {'a': 1, 'b': 1, '_stem': True, '_stopw': True}
        src_sum_peyrards = CallPeyrardforDataset('duc', ftype, **kwargs)
        sumfn_peyrards = {}
        for srcfn, sum_pyrds in src_sum_peyrards.items():
            sumfn_peyrards.update(sum_pyrds)
        DelUnselectOpt(sumfn_peyrards, select_opts=pyrd_opts)
        metric_sumfn2vals['peyrard'] = sumfn_peyrards
    if nov_opts is not None:
        kwargs = {'omega': 8, '_stem': False, '_stopw': False}
        sumfn_novs = CallNoveltyforDataset('duc', ftype, **kwargs)
        DelUnselectOpt(sumfn_novs, select_opts=nov_opts)
        metric_sumfn2vals['novelty'] = sumfn_novs
    if jcd_opts is not None:
        kwargs = {'pen_gap': True, 'rdd_thr': 0.7, '_stem': False, '_stopw': False}
        sumfn_jcds = CallJCDforDataset('duc', ftype, **kwargs)
        DelUnselectOpt(sumfn_jcds, select_opts=jcd_opts)
        metric_sumfn2vals['jcd'] = sumfn_jcds
    if lolch_opts is not None:
        kwargs = {'coref_opt': True, 'dist_opt': False}
        src_sum_lolchs = CallLolCHforDataset('duc', ftype, **kwargs)
        sumfn_lolchs = {}
        for srcfn, sum_lolch in src_sum_lolchs.items():
            sumfn_lolchs.update(sum_lolch)
        DelUnselectOpt(sumfn_lolchs, select_opts=lolch_opts)
        metric_sumfn2vals['lolch'] = sumfn_lolchs
    return metric_sumfn2vals


def GetAvgSysCrrWithMan(sysID_avgman, sysID_avgval, method='pearson', ftype='p100'):
    man_val_crrs = {}
    for _name in sysID_avgman.index:
        avgman = sysID_avgman.loc[_name]
        for _opt in sysID_avgval.index:
            avgval = sysID_avgval.loc[_opt]
            man_val_crrs[(_name, _opt)] = avgval.corr(avgman, method=method)
    print("==== Correlation Coefficients with Man Scores on DUC", ftype.upper(), "====")
    for (_name, _opt), _corr in man_val_crrs.items():
        print(_name, _opt, ':', "{:.2f}".format(_corr))
    return man_val_crrs


# ==== CheckDUCSysAvgCrr: get the crr of avg-quality-factor with avg-human-scores for each summarizers ====
def CheckDUCSysAvgCrr(ftype='p100', sum_fnpt=duc_sys_psnpt, qual_type='fidelity', **kwargs):
    sumfn_ref_manvals, Quality_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts(ftype, qual_type)
    sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)

    # ---- get sysID to avg-man-score dict ----
    sysID_sumfn_manvals, sysID_avgman = GetDUCSysID2AvgVals(sumfn_manvals, sum_fnpt)
    # ---- Get fidelity values for each summary file ----
    sumfn_quals = {}
    for srcfn in Quality_dict:
        for sumfn in Quality_dict[srcfn]:
            sumfn_quals[sumfn] = Quality_dict[srcfn][sumfn]

    metric_sumfn2vals = {qual_type: sumfn_quals}
    metric_sumfn2vals.update(GetMetricSumfn2Vals(sumfn_ref_manvals, ftype, **kwargs))
    # ---- get sysID to avg-quality-value dict ----
    sysID_sumfn_quals, sysID_avgqual = GetSysID2AvgQual(metric_sumfn2vals, sum_fnpt, sumfn_manvals)
    # ---- Calculate the correlation of average quality values with average human scores ----
    return GetAvgSysCrrWithMan(sysID_avgman, sysID_avgqual, ftype=ftype)


def GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, sumfn_metrics, metric_opts):
    man_metric_srcfn2crrs = {(_nm, _opt): {} for (_nm, _opt) in itertools.product(manval_names, metric_opts)}
    for _nm in manval_names:
        for srcfn, sumfnset in srcfn_sumfnset.items():
            manval_series = pd.Series({sumfn: sumfn_manvals[sumfn][_nm] for sumfn in sumfnset})
            for _opt in metric_opts:
                metric_series = pd.Series({sumfn: sumfn_metrics[sumfn][_opt] for sumfn in sumfnset})
                metric_crr = metric_series.corr(manval_series, method='pearson')
                if not math.isnan(metric_crr):
                    man_metric_srcfn2crrs[(_nm, _opt)][srcfn] = metric_crr
    return man_metric_srcfn2crrs


# ---- prepare data for crr-snippets ----
def GetManOptTagSrcfns(metric_srcfn2crrs):
    man2opt2tag2srcfns = {_nm: {} for (_nm, metric_opt) in metric_srcfn2crrs}
    crrtags = [str(round(snip, 1)) for snip in np.linspace(-1, 1, 21)]
    for (_nm, _opt), srcfn2crr in metric_srcfn2crrs.items():
        tag2srcfns = {tag: [] for tag in crrtags}
        for srcfn, _crr in srcfn2crr.items():
            _tag = str(round(_crr, 1))
            _tag = '0.0' if _tag == '-0.0' else _tag
            tag2srcfns[_tag].append(srcfn)
        man2opt2tag2srcfns[_nm][_opt] = tag2srcfns
    return man2opt2tag2srcfns, crrtags


# ---- prepare data for crr-snippets ----
def GetManOptTagSrcfns_hist(metric_srcfn2crrs):
    man2opt2srccrrs = {_nm: {} for (_nm, metric_opt) in metric_srcfn2crrs}
    for (_nm, _opt), srcfn2crr in metric_srcfn2crrs.items():
        srccrrs = [_crr for srcfn, _crr in srcfn2crr.items()]
        man2opt2srccrrs[_nm][_opt] = srccrrs
    return man2opt2srccrrs


# ==== CheckDUCSumSeriesFidCrrs: check each source's summaries' Fidelity and ROUGE correlation with human-scores ====
def CheckDUCSumSeriesFidCrrs(ftype='p100', fid_opts={'0.5'}, **kwargs):
    sumfn_ref_manvals, Fidelity_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts(ftype, 'fidelity')
    # ---- Get man evaluation scores for each summary file ----
    sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)
    # ---- Get fidelity values for each summary file ----
    srcfn_sumfnset, sumfn_fidvals = GetDUCFnsetsQuals(sumfn_ref_manvals, Fidelity_dict)

    # ---- get sumfn2vals for each metric ----
    metric_sumfn2vals = {'fidelity': sumfn_fidvals}
    metric_sumfn2vals.update(GetMetricSumfn2Vals(sumfn_ref_manvals, ftype, **kwargs))
    # ---- get delete sumfn from srcfn_sumfnset that do not have all values on all metrics ----
    common_sumfn_set = GetCommonKeySet(metric_sumfn2vals)
    for srcfn, sumfnset in srcfn_sumfnset.items():
        srcfn_sumfnset[srcfn] = sumfnset.intersection(common_sumfn_set)
    # ---- man_metric_src2crrs: {(manval_name, metric_opt): {srcfn: sumseries_metricvalue_crr_with_manscores}} ----
    metric_srcfn2crrs = {}
    if fid_opts is not None:
        fid_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['fidelity'], fid_opts)
        metric_srcfn2crrs.update(fid_srcfn2crrs)
    if kwargs.get('rouge_opts') is not None:
        rouge_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['rouge'], kwargs.get('rouge_opts'))
        metric_srcfn2crrs.update(rouge_srcfn2crrs)
    if kwargs.get('bleu_opts') is not None:
        bleu_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['bleu'], kwargs.get('bleu_opts'))
        metric_srcfn2crrs.update(bleu_srcfn2crrs)
    if kwargs.get('pyrd_opts') is not None:
        pyrd_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['peyrard'], kwargs.get('pyrd_opts'))
        metric_srcfn2crrs.update(pyrd_srcfn2crrs)
    # ---- Delete crr of source-file that has value on single metric ----
    metric_srcfn2crrs = DelUniqueInnerKeys(metric_srcfn2crrs)
    # ---- Show the expection and variance ----
    for _nm, srcfn2crrs in metric_srcfn2crrs.items():
        pearson_dist = np.array(list(srcfn2crrs.values()))
        if _nm[1] in fid_opts:
            print('Fidelity: exp. %.4f  var. %.4f' % (np.nanmean(pearson_dist), np.nanstd(pearson_dist)))
        else:
            print(_nm[1].title()+': exp. %.4f  var. %.4f' % (np.nanmean(pearson_dist), np.nanstd(pearson_dist)))
    # # ---- prepare data for crr-snippets ----
    # man2opt2tag2srcfns, crrtags = GetManOptTagSrcfns(metric_srcfn2crrs)
    # # ---- draw crr-snippets bar figures ----
    # for _nm, opt2tag2srcfns in man2opt2tag2srcfns.items():
    #     opt2srcfnums = {}
    #     for _opt, tag2srcfns in opt2tag2srcfns.items():
    #         srcfnums = [len(tag2srcfns[tag]) for tag in crrtags]
    #         if _opt in fid_opts:
    #             opt2srcfnums['Fidelity'] = srcfnums
    #             # opt2srcfnums['Fidelity-'+_opt] = srcfnums
    #         else:
    #             opt2srcfnums[_opt] = srcfnums
    #     # for opt, srcfnums in opt2srcfnums.items():
    #     #     print(opt, sum(srcfnums), srcfnums)
    #     bar_title = "DUC-"+ftype.title()+" Crr. distribution of Fidelity and Baselines (ref:" +kwargs.get('refopt')+ ")"
    #     DrawBars(opt2srcfnums, crrtags, bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    # for _nm, opt2srccrrs in GetManOptTagSrcfns(metric_srcfn2crrs).items():
    #     optslist = []
    #     for _opt in list(opt2srccrrs.keys()):
    #         if _opt in fid_opts:
    #             # opt2srccrrs['Fidelity-' + _opt] = opt2srccrrs.pop(_opt)
    #             opt2srccrrs['Fidelity'] = opt2srccrrs.pop(_opt)
    #             optslist.append('Fidelity')
    #         else:
    #             optslist.append(_opt)
    #     bar_title = "DUC-"+ftype.title()+" Crr. distribution of Fidelity and Baselines (ref:"+kwargs.get('refopt')+")"
    #     DrawHists(opt2srccrrs, optslist, bar_title=bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    return metric_srcfn2crrs


# ---- CheckDUCSumSeriesCCcrrs: check each source's summaries' Conciseness and JCD correlation with human-scores ----
def CheckDUCSumSeriesCCcrrs(ftype='p100', cc_opts={'avg'}, **kwargs):
    sumfn_ref_manvals, Concise_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts(ftype, 'concise')
    # ---- Get quality metric values for each summary file ----
    srcfn_sumfnset, sumfn_concise = GetDUCFnsetsQuals(sumfn_ref_manvals, Concise_dict)
    # ---- Get man evaluation scores for each summary file ----
    sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)

    metric_sumfn2vals = {'concise': sumfn_concise}
    metric_sumfn2vals.update(GetMetricSumfn2Vals(sumfn_ref_manvals, ftype, **kwargs))

    # ---- get delete sumfn from srcfn_sumfnset that do not have all values on all metrics ----
    common_sumfn_set = GetCommonKeySet(metric_sumfn2vals)
    for srcfn, sumfnset in srcfn_sumfnset.items():
        srcfn_sumfnset[srcfn] = sumfnset.intersection(common_sumfn_set)

    # ---- metric_srcfn2crrs: {(manval_name, metric_opt): {srcfn: sumseries_metricvalue_crr_with_manscores}} ----
    metric_srcfn2crrs = {}
    if cc_opts is not None:
        cc_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, sumfn_concise, cc_opts)
        metric_srcfn2crrs.update(cc_srcfn2crrs)
    if kwargs.get('jcd_opts') is not None:
        jcd_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['jcd'], kwargs.get('jcd_opts'))
        metric_srcfn2crrs.update(jcd_srcfn2crrs)
    if kwargs.get('pyrd_opts') is not None:
        pyrd_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['peyrard'], kwargs.get('pyrd_opts'))
        metric_srcfn2crrs.update(pyrd_srcfn2crrs)
    if kwargs.get('nov_opts') is not None:
        novel_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['novelty'], kwargs.get('nov_opts'))
        metric_srcfn2crrs.update(novel_srcfn2crrs)
    # ---- Delete crr of source-file that has value on single metric ----
    metric_srcfn2crrs = DelUniqueInnerKeys(metric_srcfn2crrs)
    # ---- Show the expection and variance ----
    for _nm, srcfn2crrs in metric_srcfn2crrs.items():
        pearson_dist = np.array(list(srcfn2crrs.values()))
        if _nm[1] in cc_opts:
            print('Conciseness: exp. %.4f  var. %.4f' % (np.nanmean(pearson_dist), np.nanstd(pearson_dist)))
        else:
            print(_nm[1].title() + ': exp. %.4f  var. %.4f' % (np.nanmean(pearson_dist), np.nanstd(pearson_dist)))
    # # ---- prepare data for crr-snippets ----
    # man2opt2tag2srcfns, crrtags = GetManOptTagSrcfns(metric_srcfn2crrs)
    # # ---- draw crr-snippets bar figures ----
    # for _nm, opt2tag2srcfns in man2opt2tag2srcfns.items():
    #     opt2srcfnums = {}
    #     for _opt, tag2srcfns in opt2tag2srcfns.items():
    #         srcfnums = [len(tag2srcfns[tag]) for tag in crrtags]
    #         if _opt in cc_opts:
    #             opt2srcfnums['Conciseness'] = srcfnums
    #         else:
    #             opt2srcfnums[_opt.split('-')[0]] = srcfnums
    #         # print(_opt, sum(srcfnums), srcfnums)
    #     bar_title = "DUC-" + ftype.title() + " Crr. distribution of Conciseness and Baselines"
    #     DrawBars(opt2srcfnums, crrtags, bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    # return metric_srcfn2crrs


# ==== CheckDUCSumSeriesCHCrrs: check each source's summaries' coherence with human-scores ====
def CheckDUCSumSeriesCHCrrs(ftype='p100', ch_opts={"coherence"}, **kwargs):
    sumfn_ref_manvals, Coherent_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts(ftype, 'coherence')
    # ---- Get quality metric values for each summary file ----
    srcfn_sumfnset, sumfn_coherent = GetDUCFnsetsQuals(sumfn_ref_manvals, Coherent_dict)
    # ---- Get man evaluation scores for each summary file ----
    sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)

    # ---- get sumfn2vals for each metric ----
    metric_sumfn2vals = {"Coherence": sumfn_coherent}
    metric_sumfn2vals.update(GetMetricSumfn2Vals(sumfn_ref_manvals, ftype, **kwargs))

    # ---- get delete sumfn from srcfn_sumfnset that do not have all values on all metrics ----
    common_sumfn_set = GetCommonKeySet(metric_sumfn2vals)
    for srcfn, sumfnset in srcfn_sumfnset.items():
        srcfn_sumfnset[srcfn] = sumfnset.intersection(common_sumfn_set)

    # ---- metric_srcfn2crrs: {metric_opt: {srcfn: crr_withman_value}} ----
    metric_srcfn2crrs = {}
    if ch_opts is not None:
        ch_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals["Coherence"], ch_opts)
        metric_srcfn2crrs.update(ch_srcfn2crrs)
    if kwargs.get('lolch_opts') is not None:
        lolch_srcfn2crrs = GetSumSeriesCrrWithMan(srcfn_sumfnset, sumfn_manvals, manval_names, metric_sumfn2vals['lolch'], kwargs['lolch_opts'])
        metric_srcfn2crrs.update(lolch_srcfn2crrs)

    # ---- Delete crr of source-file that has value on single metric ----
    metric_srcfn2crrs = DelUniqueInnerKeys(metric_srcfn2crrs)

    # ---- man2opt2tag2srcfns: {(manval_name, metric_opt): {srcfn: sumseries_metricvalue_crr_with_manscores}} ----
    # ---- crrtags: a series of Pearson's correlation interval tags ----
    man2opt2tag2srcfns, crrtags = GetManOptTagSrcfns(metric_srcfn2crrs)

    # ---- draw crr-snippets bar figures ----
    for _nm, opt2tag2srcfns in man2opt2tag2srcfns.items():
        opt2srcfnums = {}
        for _opt, tag2srcfns in opt2tag2srcfns.items():
            opt2srcfnums[_opt] = [len(tag2srcfns[tag]) for tag in crrtags]
        bar_title = "DUC-" + ftype.title() + " Crr. distribution of Coherence and Baselines"
        DrawBars(opt2srcfnums, crrtags, bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    return metric_srcfn2crrs


#######################################################################################
# ---------------------------------- Test Functions --------------------------------- #
#######################################################################################
def DrawPie(label2size_dict, pie_title='PIE', figsize=(8, 9), explode_labels=None, labeldistance=1.1,
            shadow=False, startangle=90, pctdistance=0.6, ltxt_size=(30), ptxt_size=(20)):
    # cmap = plt.get_cmap('Spectral')
    # colors = [cmap(i) for i in np.linspace(0, 1, len(label2size_dict))]
    cmap = {('fidelity',): '#FF8C00',  ('rouge',): '#FFD700', ('bleu',): '#3CB371',
            ('rouge', 'fidelity'): '#48D1CC', ('bleu', 'fidelity'): '#6495ED', ('rouge', 'bleu'): '#9978E6',
            ('rouge', 'bleu', 'fidelity'): '#9029BF', ('wrong',): '#B22222',
            ('concise',): '#4169E1', ('jcd',): '#3CB371', ('concise', 'jcd'): '#9029BF',
            ('coherence',): '#9029BF'}
    plt.figure(figsize=figsize)

    labels, sizes, explodes, colors = [], [], [], []
    for label, size in label2size_dict.items():
        labels.append(label)
        sizes.append(size)
        if explode_labels is not None and label in explode_labels:
            explodes.append(0.05)
        else:
            explodes.append(0)
        label_set = set(map(lambda x: x.split('-')[0].lower(), label.split('+')))
        for key, clr in cmap.items():
            if set(key) == label_set:
                colors.append(clr)

    if len(colors) != len(labels):
        colors = list(cmap.values())

    patches, l_txt, p_txt = plt.pie(sizes, explode=explodes, colors=colors, labels=labels, labeldistance=labeldistance,
                                    autopct='%4.2f%%', shadow=shadow, startangle=startangle, pctdistance=pctdistance)
    for t in l_txt:
        t.set_size = ltxt_size

    for t in p_txt:
        t.set_size = ptxt_size

    plt.axis('equal')
    plt.title(pie_title)
    plt.legend()
    plt.show()


def DrawHists(type2series, typelist, bar_title='BAR', x_label='', y_label='', figsize=(8, 8), lgdsize=12, tsize=14):
    cmap = {'fidelity': '#FF8C00', 'rouge': '#FFD700', 'bleu': '#2E8B57', 'relevance': '#EEA2AD',
            'conciseness': '#1E90FF', 'jcd': '#FFD700', 'novelty': '#43CD80', 'redundancy': '#EEA2AD',
            'coherence': '#9029BF'}
    colors = list(cmap.values())
    n_bins = 20
    fig, ax = plt.subplots(figsize=figsize)
    # ---- 这两行代码解决 plt 中文显示的问题 ----
    # plt.rcParams['font.sans-serif'] = ['SimHei']
    # ---- 用来正常显示负号 ----
    plt.rcParams['axes.unicode_minus'] = False

    for idx, type in enumerate(typelist):
        clr = cmap.get(type.split('-')[0].lower(), colors[idx])
        ax.hist(type2series[type], bins=n_bins, histtype='bar', label=type, color=clr, alpha=1-0.2*idx)

    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.legend(fontsize=lgdsize)
    plt.title(bar_title, fontsize=tsize)
    plt.show()


def DrawBars(type2counts, x_coords, bar_title='BAR', x_label='', y_label='', figsize=(8, 8), lgdsize=12, ttlsize=14):
    # cmap = plt.get_cmap('Spectral')
    # colors = [cmap(i) for i in np.linspace(0, 1, len(type2counts))]
    cmap = {'fidelity': '#FF8C00', 'rouge': '#FFD700', 'bleu': '#2E8B57', 'relevance': '#EEA2AD',
            'conciseness': '#1E90FF',  'jcd': '#00EEEE', 'novelty': '#43CD80', 'redundancy': '#EEDC82',
            'coherence': '#9029BF', 'localcoherence': '#FF83FA'}
    colors = list(cmap.values())

    plt.figure(figsize=figsize)

    # # ---- 这两行代码解决 plt 中文显示的问题 ----
    # plt.rcParams['font.sans-serif'] = ['SimHei']
    # plt.rcParams['axes.unicode_minus'] = False

    bar_width = 0.3
    step_width = (len(type2counts)+1) * bar_width
    start_loc_index = np.arange(0, step_width*len(x_coords)-bar_width,  step_width)

    for idx, (type, counts) in enumerate(type2counts.items()):
        loc_index = start_loc_index + idx * bar_width
        clr = cmap.get(type.split('-')[0].lower(), colors[idx])
        plt.bar(loc_index, height=counts, width=bar_width, color=clr, label=type)

    plt.legend(fontsize=lgdsize)
    plt.xticks(start_loc_index + bar_width*(len(type2counts)-1)/2, x_coords)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(bar_title, fontsize=ttlsize)

    plt.show()


def ObserveConcise():
    sumfn_ref_manvals, Concise_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts('p100', 'concise')
    srcfn_sumfnset, sumfn_concise = GetDUCFnsetsQuals(sumfn_ref_manvals, Concise_dict)
    sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)
    for sumfn, concise in sumfn_concise.items():
        print(sumfn + ',' + '{:.4f}'.format(concise['avg']) + ',' + '{:.4f}'.format(sumfn_manvals[sumfn][manval_names[0]]))


def GroupTeamingGraph():
    bar_title = "DUC-P100 Crr. distribution of Coherence on Q5+Q7"
    opt2srcfnums = {'Coherence-avg': [0, 0, 0, 5, 5, 0, 2, 4, 10, 10, 18, 20, 25, 15, 18, 8, 6, 2, 0, 0, 0]}
    DrawBars(opt2srcfnums, [str(round(snip, 1)) for snip in np.linspace(-1, 1, 21)], bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    bar_title = "DUC-M200 Crr. distribution of Coherence on Q5+Q7"
    opt2srcfnums = {'Coherence-avg': [0, 0, 0, 1, 0, 0, 2, 2, 4, 4, 5, 7, 6, 10, 9, 9, 5, 1, 0, 0, 0]}
    DrawBars(opt2srcfnums, [str(round(snip, 1)) for snip in np.linspace(-1, 1, 21)], bar_title, x_label='Crr Intervals', y_label='Amount of Source Texts')
    # ---- Draw Pie Figures ----
    label2sumpairs = {'Wrong': 1283, 'Coherence-avg': 1801}
    label2size = {label: fnpairs for label, fnpairs in label2sumpairs.items()}
    pairnum_str = "(summary-pairs: 3084)"
    pie_title = '; '.join(['DUC-P100 Coherence-avg on Q5+Q7', pairnum_str])
    DrawPie(label2size, pie_title=pie_title)
    label2sumpairs = {'Wrong': 516, 'Coherence-avg': 780}
    label2size = {label: fnpairs for label, fnpairs in label2sumpairs.items()}
    pairnum_str = "(summary-pairs: 1296)"
    pie_title = '; '.join(['DUC-M200 Coherence-avg on Q5+Q7', pairnum_str])
    DrawPie(label2size, pie_title=pie_title)


def WriteCHIntoExcel(metric_sumfn2vals, srcfn_sumfnset, scorefp):
    workbook = xlwt.Workbook(encoding='utf-8')
    for metric, sumfn2vals in metric_sumfn2vals.items():
        worksheet = workbook.add_sheet(metric, cell_overwrite_ok=True)
        srcfn_sumfn2val = {}
        for srcfn, sumfnset in srcfn_sumfnset.items():
            if srcfn not in srcfn_sumfn2val:
                srcfn_sumfn2val[srcfn] = {}
            for sumfn in sumfnset:
                if sumfn in sumfn2vals:
                    srcfn_sumfn2val[srcfn][sumfn] = list(sumfn2vals[sumfn].values())
        for srcfn in list(srcfn_sumfn2val.keys()):
            if not srcfn_sumfn2val[srcfn]:
                srcfn_sumfn2val.pop(srcfn)
        srcfn_list, sysIDs = sorted(list(srcfn_sumfn2val.keys())), {}
        for row, srcfn in enumerate(srcfn_list):
            worksheet.write(row + 1, 0, srcfn)
            for sumfn, _vals in srcfn_sumfn2val[srcfn].items():
                sysid = sumfn.split('.')[-1]
                if sysid not in sysIDs:
                    sysIDs[sysid] = len(sysIDs)
                col = sysIDs[sysid]
                worksheet.write(row + 1, col + 1, _vals[0])
        worksheet.write(0, 0, "SRC-Fname", xlwt.easyxf('font: bold on'))
        for header, col in sysIDs.items():
            worksheet.write(0, col + 1, header, xlwt.easyxf('font: bold on'))
    workbook.save(scorefp)


#######################################################################################
# ---------------------------------- Main function ---------------------------------- #
#######################################################################################
if __name__ == "__main__":
    CheckAIACLSumPairFid('acl', ['abs', 'sysA', 'wstA'], 'con', rouge_opts={'ROUGE-2-F'}, bleu_opts={'BLEU-4'},
                         srcfnpt=r"^P14-\d{4}\.xhtml", good_suffix='A.A', bad_suffix='A.99')
    # CheckAIACLSumPairFid('ai', ['abs', 'sysA', 'wstA'], 'con', rouge_opts={'ROUGE-2-F'}, bleu_opts={'BLEU-4'},
    #                      srcfnpt=r"^S00043702[0-9X]{8}\.xml", good_suffix='A.A', bad_suffix='A.99')
    # for (ftype, snpt) in [('p100', duc_sys_psnpt), ('m100', duc_sys_msnpt), ('m200', duc_sys_msnpt)]:
    #     CheckDUCSysAvgCrr(ftype, snpt, qual_type='fidelity', pyrd_opts={'Relevance'}, rouge_opts={'ROUGE-2-F'},
    #                       bleu_opts={'BLEU-4'},  refopt='same')

    # for ftype in ['p100', 'm100', 'm200']: #'p100', 'm100', 'm200'
        # CheckDUCSumSeriesFidCrrs(ftype, fid_opts={'0.5'}, pyrd_opts={'Relevance'}, rouge_opts={'ROUGE-2-F'},
        #                          bleu_opts={'BLEU-4'}, refopt='same')
        # CheckDUCSumSeriesFidCrrs(ftype, fid_opts={'0.5'}, pyrd_opts={'Relevance'}, rouge_opts={'ROUGE-2-F'},
        #                          bleu_opts={'BLEU-4'}, refopt='diff')
        # CheckDUCSumSeriesCCcrrs(ftype, cc_opts={'avg'}, jcd_opts={'JCD-avg'}, pyrd_opts={'Redundancy'},
        #                         nov_opts={'Novelty-avg'})
        # CheckDUCSumSeriesCHCrrs(ftype, ch_opts={'coherence'})
    # ftype = 'p100'
    # sumfn_ref_manvals, Coherent_dict, manval_name2idx, manval_func = GetDUCManvalQualDicts(ftype, 'coherence')
    # srcfn_sumfnset, sumfn_coherent = GetDUCFnsetsQuals(sumfn_ref_manvals, Coherent_dict)
    # sumfn_manvals, manval_names = GetDUCSumfn2Manval(sumfn_ref_manvals, manval_name2idx, manval_func)
    # metric_sumfn2vals = DelUniqueInnerKeys({"Coherence": sumfn_coherent, "ManScore": sumfn_manvals})
    # scorefp = os.path.join(duc_score_dir, ftype.upper() + "_coherence.xls")
    # WriteCHIntoExcel(metric_sumfn2vals, srcfn_sumfnset, scorefp)
    # vpldsim = [(1, 0, 0), (0, 1, 0), (0, 0, 1), (1, 1, 0), (1, 0, 1), (1, 1, 1)]
    # WriteDatasetCoherenceIntoExcel('duc', ['m100', 'm100r'], duc_score_dir, vpldsim=vpldsim)
    # WriteDatasetCoherenceIntoExcel('duc', ['m200', 'm200r'], duc_score_dir, vpldsim=vpldsim)
    # WriteDatasetCoherenceIntoExcel('duc', ['p100', 'p100r'], duc_score_dir, vpldsim=vpldsim)
    # pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo('acl', 'rnd')
    # src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    # sumfn_selflinks = {}
    # for srcfp in src_sum_fpalign_dict:
    #     for sumfp in src_sum_fpalign_dict[srcfp]:
    #         sumfn = os.path.basename(sumfp)
    #         SumSLN = GetFileCacheDatas(sumfp, 'SumSLN', pk_dir)
    #         for l in SumSLN.Links:
    #             if l.l_node == l.r_node:
    #                 if sumfn not in sumfn_selflinks:
    #                     sumfn_selflinks[sumfn] = []
    #                 sumfn_selflinks[sumfn].append((l._label, l._type, l.times, (l.l_node._label, l.r_node._label)))
    #
    # for fid, (sumfn, selflinks) in enumerate(sumfn_selflinks.items()):
    #     print("-----------", fid, ":", sumfn, "--------------")
    #     for link in selflinks:
    #         print("\t", link)
    # vpldsim = [(1, 0, 0)]
    # WriteDatasetCoherenceIntoExcel('duc', ['p100', 'p100r'], duc_score_dir, vpldsim=vpldsim)