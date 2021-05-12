# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
import os
import re
import codecs
import pickle
import csv
from collections import Iterable
import xlwt
from itertools import chain, combinations
from tkinter.messagebox import showerror

# ========= Path for Stanford Parser and Corpus =========
corpus_dir = os.path.join(os.getcwd(), "Corpus")
coreNLP_path = os.path.join(os.getcwd(), "stanford-corenlp-full-2018-02-27")


# ============ Paths for ACL Dataset ===========
acl_dataset = os.path.join(os.getcwd(), "ACL-Dataset")
acl_score_dir = os.path.join(acl_dataset, "ScoreTables")
acl_pkdir = os.path.join(acl_dataset, "PickleFiles")
# ---- source text files and summary files directory ----
acl_fdir = os.path.join(acl_dataset, "SourceFiles")
acl_fsdir = {
    'abs': (os.path.join(acl_dataset, "SourceFiles_abs"), os.path.join(acl_dataset, "Summary_abs"), 'p'),
    'con': (os.path.join(acl_dataset, "SourceFiles_con"), os.path.join(acl_dataset, "Summary_con"), 'p'),
    'sysA': (os.path.join(acl_dataset, "SourceFiles_abs"), os.path.join(acl_dataset, "Summary_sysA"), 'p'),
    'sysC': (os.path.join(acl_dataset, "SourceFiles_con"), os.path.join(acl_dataset, "Summary_sysC"), 'p'),
    'wstA': (os.path.join(acl_dataset, "SourceFiles_abs"), os.path.join(acl_dataset, "Summary_wstA"), 'p'),
    'wstC': (os.path.join(acl_dataset, "SourceFiles_con"), os.path.join(acl_dataset, "Summary_wstC"), 'p'),
    'rnd': (os.path.join(acl_dataset, "SourceFiles_abs"), os.path.join(acl_dataset, "Summary_rnd"), 'p')
}
# ---- regexp patterns for source-file names and summary-file names ----
acl_fnpt = r"^(P14-\d{4}\.xhtml)\.[AC]$"
acl_snpt = r"(P14-\d{4}\.xhtml)\.[AC]\.[0-9A-Z]+"
acl_std_snpt = r"(P14-\d{4}\.xhtml)\.[AC]\.[AB]"
# acl_std_snpt = r"(P14-\d{4}\.xhtml)\.[AC]\.03"
acl_sys_snpt = r"(P14-\d{4}\.xhtml)\.[AC]\.[0-9]+"

# ============ Paths for AI Dataset ===========
ai_dataset = os.path.join(os.getcwd(), "AI-Dataset")
ai_score_dir = os.path.join(ai_dataset, "ScoreTables")
ai_pkdir = os.path.join(ai_dataset, "PickleFiles")
# ---- source text files and summary files directory ----
ai_fdir = os.path.join(ai_dataset, "SourceFiles")
ai_fsdir = {
    "abs": (os.path.join(ai_dataset, "SourceFiles_abs"), os.path.join(ai_dataset, "Summary_abs"), 'p'),
    "con": (os.path.join(ai_dataset, "SourceFiles_con"), os.path.join(ai_dataset, "Summary_con"), 'p'),
    "sysA": (os.path.join(ai_dataset, "SourceFiles_abs"), os.path.join(ai_dataset, "Summary_sysA"), 'p'),
    "sysC": (os.path.join(ai_dataset, "SourceFiles_con"), os.path.join(ai_dataset, "Summary_sysC"), 'p'),
    "wstA": (os.path.join(ai_dataset, "SourceFiles_abs"), os.path.join(ai_dataset, "Summary_wstA"), 'p'),
    "wstC": (os.path.join(ai_dataset, "SourceFiles_con"), os.path.join(ai_dataset, "Summary_wstC"), 'p'),
    "rnd": (os.path.join(ai_dataset, "SourceFiles_abs"), os.path.join(ai_dataset, "Summary_rnd"), 'p'),
}
# ---- regexp patterns for source-file names and summary-file names ----
ai_fnpt = r"^(S00043702[0-9X]{8})\.xml(?:\.[ACI])?$"
ai_snpt = r"^(S00043702[0-9X]{8})\.xml\.[ACI]\.[0-9A-Z]+$"
ai_std_snpt = r"^(S00043702[0-9X]{8})\.xml\.[ACI]\.[ABD]$"
# ai_std_snpt = r"^(S00043702[0-9X]{8})\.xml\.[ACI]\.03$"
ai_sys_snpt = r"^(S00043702[0-9X]{8})\.xml\.[ACI]\.[0-9]+$"

# ============ Paths for DUC Dataset ===========
duc_dataset = os.path.join(os.getcwd(), "DUC-Dataset")
duc_score_dir = os.path.join(duc_dataset, "ScoreTables")
duc_pkdir = os.path.join(duc_dataset, "PickleFiles")
# ---- source text files and summary files directory ----
duc_fsdir = {
    'p100': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_p100"), 'p'),
    'm100': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_m100"), 'm'),
    'm200': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_m200"), 'm'),
    'p100r': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_p100_R"), 'p'),
    'm100r': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_m100_R"), 'm'),
    'm200r': (os.path.join(duc_dataset, "SourceFiles"), os.path.join(duc_dataset, "Summary_m200_R"), 'm'),
}
# ---- regexp patterns for source-file names and summary-file names ----
duc_fnpt = r"^([A-Z0-9]{5,}-[0-9]{3,})\.html$"
duc_dirnpt = r"^(D[0-9]{3})"
duc_psnpt = r"^(D[0-9]{3})\.([A-Z0-9]{5,}-[0-9]{3,})\.html\.[A-Z0-9]+$"
duc_std_psnpt = r"^(D[0-9]{3})\.([A-Z0-9]{5,}-[0-9]{3,})\.html\.[A-Z]+$"
duc_sys_psnpt = r"^(D[0-9]{3})\.([A-Z0-9]{5,}-[0-9]{3,})\.html\.[0-9]+$"
duc_msnpt = r"^(D[0-9]{3})\.M\.(?:010|050|100|200)\.html\.[A-Z0-9]+$"
duc_std_msnpt = r"^(D[0-9]{3})\.M\.(?:010|050|100|200)\.html\.[A-Z]+$"
duc_sys_msnpt = r"^(D[0-9]{3})\.M\.(?:010|050|100|200)\.html\.[0-9]+$"


#######################################################################################
# --------------------------------- Get File name/path list ------------------------- #
#######################################################################################
# ---- 获取当前文件夹下文件名列表 ----
def GetFileNameList(filedir, depth=1):
    if not os.path.isdir(filedir):
        showerror('Error!', 'no dir to be read')
        return []
    files = os.listdir(filedir)
    filenamelist = []
    for f in files:
        if os.path.isfile(os.path.join(filedir, f)):
            filenamelist.append(f)
    return filenamelist


def GetFileDirPaths(filedir, depth=1):
    if os.path.isfile(filedir):
        return [filedir], []
    if not os.path.isdir(filedir):
        showerror('Error!', 'no dir to be read')
        return [], []
    fplist, dplist = [], []
    allpaths = [os.path.join(filedir, nm) for nm in os.listdir(filedir)]
    for itertime in range(depth):
        if not allpaths:
            break
        # print('get', itertime+1, "th layer files ...")
        new_allpaths = []
        for temp_path in allpaths:
            if os.path.isfile(temp_path):
                fplist.append(temp_path)
            else:
                dplist.append(temp_path)
                new_allpaths.extend([os.path.join(temp_path, nm) for nm in os.listdir(temp_path)])
        allpaths = new_allpaths
    return fplist, dplist


#######################################################################################
# ------------------------------- File Content related ------------------------------ #
#######################################################################################
# ----- Write strings into files with the code type 'UTF-8' ----
def WriteFile(fpath, txtstr, ctype='utf-8'):
    ut = GetUnicode(txtstr)
    f = codecs.open(fpath, 'w+', ctype)
    f.write(ut)
    f.close()


# ----- Getting the string store in the fpath with the 'UTF-8' code type ----
def ReadFile(fpath, codetype='utf-8-sig'):
    try:
        f = codecs.open(fpath, 'r', codetype)
        fstring = f.read()
        f.close()
        return fstring
    except IOError:
        print('Error in opening file', fpath)
        return None


# -------------------- Dump data into a file using pickle------------------------------
def Dumppickle(fpath, result):
    newdir, fname = os.path.split(fpath)
    if not os.path.isdir(newdir):
        os.makedirs(newdir)
    fp = open(fpath, 'wb')
    pickle.dump(result, fp)
    fp.close()
    return


# ----------------------- Load data from a file using pickle------------------------------
def Loadpickle(fpath):
    if not os.path.isfile(fpath):
        raise Exception('There is no file named as ' + fpath)
    fp = open(fpath, 'rb')
    result = pickle.load(fp)
    fp.close()
    return result


def ReadTSV(fp):
    frequencies = {}
    with open(fp) as tsv:
        tsv_reader = csv.reader(tsv, delimiter="\t")
        for row in tsv_reader:
            frequencies[row[0]] = int(row[1])
    return frequencies


#######################################################################################
# --------------------------- Rename and Delete Files ------------------------------- #
#######################################################################################
def RenameFilesDirs(rawdir, raw_npt, new_npt, type="file", func=None):
    fplist, dplist = GetFileDirPaths(rawdir, depth=2)
    if type == "file":
        allpaths = fplist
    else:
        allpaths = dplist
    for fp in allpaths:
        fname, fdir = os.path.basename(fp), os.path.dirname(fp)
        mt = re.match(raw_npt, fname)
        if mt is None:
            continue
        newfname = new_npt
        for idx, seg in enumerate(mt.groups()):
            if func is not None:
                seg = func(seg)
            newfname = re.sub(r"\(#"+str(idx)+"\)", seg, newfname)
        os.rename(fp, os.path.join(fdir, newfname))
        print(fname, "-->", newfname)


def DeleteFiles(file_dir, fnpt):
    fplist, dirlist = GetFileDirPaths(file_dir, depth=10)
    for fp in fplist:
        fname = os.path.basename(fp)
        if re.match(fnpt, fname) is not None:
            print("Delete file", fname, "...")
            os.remove(fp)


#######################################################################################
# --------------------------------- Operations on list ------------------------------ #
#######################################################################################
def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))


# ---- 从一个string类型对象列表中删除空的string对象 ----
def DelEmptyString(strlist):
    i = 0
    while i < len(strlist):
        if strlist[i] == None or len(strlist[i].strip()) == 0:
            del strlist[i]
        else:
            i += 1
    return strlist


# ---- ListFlatten flat a high-dimensional list into a 1-dimensional list ----
def ListFlatten(lst):
    ans = []
    if isinstance(lst, Iterable):
        for templst in lst:
            ans.extend(ListFlatten(templst))
    else:
        ans.append(lst)
    return ans


# ---- FindMonoIncSeries find the monotonic increasing interger sequence in a list ----
def MonoIntSeries(lst, stride=1):
    sid_series = []
    if isinstance(lst, Iterable):
        temp_seq = [lst[0]]
        for i in lst[1:]:
            if isinstance(i, int) and isinstance(temp_seq[-1], int) and i == temp_seq[-1] + stride:
                temp_seq.append(i)
            else:
                sid_series.append(temp_seq)
                temp_seq = [i]
        sid_series.append(temp_seq)
    return sid_series


# ---- perform the 'and' operation on a bool value list ----
def BoolAND(bool_list: list) -> bool:
    flag = True
    for b in bool_list:
        if b not in [True, False, 0, 1]:
            return False
        flag = flag and b
    return flag


# ---- perform the 'or' operation on a bool value list ----
def BoolOR(bool_list: list) -> bool:
    flag = False
    for b in bool_list:
        if b not in [True, False, 0, 1]:
            return False
        flag = flag or b
    return flag


def DefKwargs(kwargs, key_defval):
    if isinstance(kwargs, dict):
        for key, defval in key_defval.items():
            if key not in kwargs:
                kwargs[key] = defval
    return kwargs


#######################################################################################
# ---------------------------- Encode and decode related ---------------------------- #
#######################################################################################
def strdecode(string, charset=None):
    if isinstance(string, str):
        return string
    if charset:
        try:
            return string.decode(charset)
        except UnicodeDecodeError:
            return _strdecode(string)
    else:
        return _strdecode(string)


def _strdecode(string):
    try:
        return string.decode('utf8')
    except UnicodeDecodeError:
        try:
            return string.decode('gb2312')
        except UnicodeDecodeError:
            try:
                return string.decode('gbk')
            except UnicodeDecodeError:
                return string.decode('gb18030')


# ---- RemoveUStrSpace: remove some character that not in ascii scope, and redundant empty character ----- #
def RemoveUStrSpace(string):
    if isinstance(string, str):
        unc = string
    else:
        unc = strdecode(string, 'utf-8')
    pattern = re.compile(r"[^\x20-\x7E]")
    nstr = pattern.sub(' ', unc)
    pattern = re.compile(r"\s+")
    nstr = pattern.sub(' ', nstr).strip()
    return nstr


# ---- Get the type sets of the input string ------
# Each set is a triple like (ctype, 1 or 0, string that is encoded according to the ctype )
# 1 means that the string can be encoded by the ctype, 0 means the string cannot be encoded by the ctype.
def GetCodeTypeSet(string, ignore=False):
    typeset = []
    if isinstance(string, str):
        d = ('utf-8', 1, string)
        typeset.append(d)
        return typeset
    else:
        codetype = ['utf-8', 'gbk', 'gb2311']
        for ctype in codetype:
            try:
                if not ignore:
                    us = string.decode(ctype)
                else:
                    us = string.decode(ctype, 'ignore')
                d = (ctype, 1, us)
                typeset.append(d)
            except Exception as e:
                d = (ctype, 0, string)
                typeset.append(d)
    return typeset


# ---- encode the input string as UTF-8----
def GetUnicode(string):
    if isinstance(string, str):
        return string
    typeset = GetCodeTypeSet(string)
    for t in typeset:
        if t[1] == 1 and t[0] == 'utf-8':
            return t[2]
        elif t[1] == 1:
            string = t[2]
    return string


#######################################################################################
# ---------------------------------- Test function ---------------------------------- #
#######################################################################################
def TestRenameFilesDirs():
    raw_dir = r"C:\Users\MerryCao\Desktop\DUC ROUGE_BLEU_PK"
    raw_npt = r"^(DUC_.+)_man_(.+)"
    new_npt = "(#0)_same_(#1)"
    RenameFilesDirs(raw_dir, raw_npt, new_npt, type="file")


def TestChangeSumName(srcfn="S0004370218303163.xml.A.", sysid="30", target="99"):
    # --- pickle data ---
    print("===== switched cached pickle data =====")
    RenameFilesDirs(ai_pkdir, srcfn + sysid + r"\.(.*)", srcfn + "TT.(#0)")
    RenameFilesDirs(ai_pkdir, srcfn + target + r"\.(.*)", srcfn + sysid + ".(#0)")
    RenameFilesDirs(ai_pkdir, srcfn + r"TT\.(.*)", srcfn + target + ".(#0)")
    print("===== switched summary file =====")
    # --- summary file ---
    RenameFilesDirs(ai_fsdir['sysA'][1], srcfn + sysid, srcfn + "TT")
    RenameFilesDirs(ai_fsdir['sysA'][1], srcfn + target, srcfn + sysid)
    RenameFilesDirs(ai_fsdir['sysA'][1], srcfn + "TT", srcfn + target)


#######################################################################################
# ---------------------------------- Main function ---------------------------------- #
#######################################################################################
if __name__ == "__main__":
    # DeleteFiles(acl_pkdir, r"P14-\d\d\d\d\.xhtml\.C\.B\.Sents\.pk")
    TestRenameFilesDirs()
    # TestChangeSumName(srcfn="S0004370218303163.xml.A.", sysid="30", target="99")