# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
import bs4
from bs4 import BeautifulSoup
import random
import shutil
import json
from ProcessFiles import *
from Utilities import *


#######################################################################################
# ----------------------- Delete or Revise Tags in HTML files ----------------------- #
#######################################################################################
# ===== IterDelTags: a function to iteratively delete specific tags from a BeautifulSoup object =====
# p_tag: a bs4 object needed to be processed
# deltags: a dict stores the tags that are needed to be deleted
# strtags: a dict stores the tags that need to convert to a string
#          An element for deltags and strtags is like: tag_name:{'attr_name:{value1, value2, value3}'}
def IterDelTags(p_tag, deltags={}, strtags={}, print_prefix=""):
    # print(print_prefix, "--------------------")
    # print(print_prefix, p_tag.name)
    if type(p_tag) not in [bs4.BeautifulSoup, bs4.element.NavigableString, bs4.element.Tag]:
        # print(print_prefix, "object not belongs to useful object!")
        try:
            p_tag.extract()
        except AttributeError:
            pass
        return
    # ---- If p_tag is just a string ----
    if type(p_tag) is bs4.element.NavigableString:
        # print(print_prefix, "Just a string")
        return
    # ---- if p_tag has children, iteratively process each child ----
    for c_tag in p_tag.contents:
        IterDelTags(c_tag, deltags, strtags, print_prefix+'\t')
    # ---- p_tag is a Tag and belongs to the tags that need to delete, or ----
    # ---- p_tag is a Tag and belongs to the tags that need to convert to a string ----
    if type(p_tag) is bs4.element.Tag and (p_tag.name in deltags or p_tag.name in strtags):
        delats, strats = deltags.get(p_tag.name, None), strtags.get(p_tag.name, None)
        delflag = delats is not None and len(delats) == 0
        strflag = strats is not None and len(strats) == 0
        for at in p_tag.attrs:
            at_values = {p_tag[at]} if type(p_tag[at]) is str else set(p_tag[at])
            if (delats is not None) and (at in delats) and (not delats[at] or len(at_values & delats[at]) > 0):
                delflag = True
            if (strats is not None) and (at in strats) and (not strats[at] or (at_values & strats[at])):
                strflag = True
        if strflag:
            # print(print_prefix, "Convert to a string ...")
            p_str = ''.join([string for string in p_tag.strings])
            if not p_str.isspace():
                p_tag.insert_before(p_str)
        if delflag or strflag:
            # print(print_prefix, "Delete this tag ...")
            p_tag.extract()
            return
    # # ----- 不好用 If a tag just contains strings, merge all strings into one ----
    # all_string = True
    # for c_tag in p_tag.contents:
    #     if type(c_tag) is not bs4.element.NavigableString:
    #         all_string = False
    #         break
    # if all_string:
    #     print(print_prefix, "all strings!")
    #     p_str = ''.join([string for string in p_tag.strings])
    #     p_tag.clear()
    #     p_tag.string = re.sub('\s+', ' ', p_str.strip())
    return


def DelTags(soup, deltags):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.NavigableString, bs4.element.Tag]:
        print("DelTags: type of the soup is error!")
        return soup
    if type(deltags) not in [list, tuple, set] or not BoolAND([type(nm) is str for nm in deltags]):
        print("DelTags: type of the deltags is error!")
        return soup
    for name in deltags:
        for del_tag in soup.find_all(name):
            del_tag.extract()
    return soup


def RenameTags(soup, name_dict={}):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.NavigableString, bs4.element.Tag]:
        print("RenameTags: type of the soup is error!")
        return soup
    if type(name_dict) is not dict:
        print("RenameTags: type of the name_dict is error!")
        return soup
    if not name_dict or not BoolAND([type(oldnm) is str and type(newnm) is str for oldnm, newnm in name_dict.items()]):
        print("RenameTags: the name_dict is empty or it is not a dict mapping string to string")
        return soup
    for oldnm in name_dict:
        for old_tag in soup.find_all(oldnm):
            old_tag.name = name_dict[oldnm]
    return soup


def UniTags(soup, unitags):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.Tag]:
        print("UniTags: type of the soup is error!")
        return soup
    if type(unitags) is not dict:
        print("UniTags: type of the unitags is error!")
        return soup
    if not unitags or not BoolAND([(type(pn) is str and type(cn) is str) for pn, cn in unitags.items()]):
        print("UniTags: the unitags is empty or it is not a dict mapping string to string")
        return soup
    for pn, cn in unitags.items():
        for ptag in soup.find_all(pn):
            child_exist = False
            for child in ptag.contents:
                if child.name != cn:
                    continue
                if not child_exist:
                    child_exist = True
                else:
                    child.extract()
    return soup


def MergeTags(soup, namelist, mrgstr=' ', insertloc=0):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.Tag]:
        print("MergeTags: type of the soup is error!")
        return soup
    if type(namelist) not in [list, set, tuple]:
        print("MergeTags: type of the namelist is error!")
        return soup
    if not namelist or not BoolAND([type(nm) is str for nm in namelist]):
        print("MergeTags: the list is empty or it is not a list of string")
        return soup
    for nm in namelist:
        all_strings, parent_names = [], []
        for tag in soup.find_all(nm):
            parent_names.append(tag.parent.name)
            for temp_string in tag.stripped_strings:
                all_strings.append(temp_string.strip())
            tag.extract()
        # ---- If no string found under the tag name nm ----
        if not all_strings:
            continue
        # ---- create new tag ----
        new_tag = soup.new_tag(nm)
        new_tag.append(mrgstr.join(all_strings))
        print("\t", new_tag)
        # ---- find the parent tag ----
        most_parent_name = Counter(parent_names).most_common(1)[0][0]
        parent_tag = soup.find(most_parent_name)
        # ---- insert new_tag into parent_tag ----
        insertloc = min(insertloc, len(parent_tag.contents)-1)
        parent_tag.insert(insertloc, new_tag)
    return soup


def DirIterDelTags(src_dir, deltags, strtags, fnpt=r"", newdir_suffix="_new"):
    base_dir = os.path.dirname(src_dir)
    # ---- Get directory for storing the new source text ----
    new_src_dir = os.path.join(base_dir, os.path.basename(src_dir) + newdir_suffix)
    if os.path.isdir(new_src_dir):
        shutil.rmtree(new_src_dir)
    os.mkdir(new_src_dir)
    # ---- Get source file path list ----
    fplist = []
    if os.path.isfile(src_dir):
        fplist = [src_dir]
    elif os.path.isdir(src_dir):
        fplist = GetFileDirPaths(src_dir, 3)[0]
    # ---- For each source file, delete tags that are not in tags ----
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(fnpt, fname) is None:
            continue
        print('\033[34m%s\033[0m' % "Process File " + fname)
        soup = BeautifulSoup(ReadFile(fp), 'lxml')
        IterDelTags(soup, deltags, strtags)
        WriteFile(os.path.join(new_src_dir, fname), soup.prettify())
    return


def DirDelTagsByName(src_dir, deltags, fnpt=r"", parser_type='lxml-xml', dirsuf="_new", filesuf=""):
    if type(deltags) not in [list, tuple, set] or not BoolAND([type(nm) is str for nm in deltags]):
        print('\033[31m%s\033[0m' % "The input of deltags is not correct! ...")
        return False
    # ---- Get overall directory for storing the new source text ----
    oldsrc_dirnms = src_dir.split('\\')
    new_src_dir = src_dir + dirsuf
    if not os.path.isdir(new_src_dir):
        os.makedirs(new_src_dir)
    # ---- Get source file path list ----
    fplist = []
    if os.path.isfile(src_dir):
        fplist = [src_dir]
    elif os.path.isdir(src_dir):
        fplist = GetFileDirPaths(src_dir, 3)[0]
    # ---- For each source file, delete tags that are not in tags ----
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(fnpt, fname) is None:
            continue
        print("Deleting tags from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), parser_type)
        DelTags(soup, deltags)
        # ---- get new file path, and writtern new source files ----
        new_fdir = os.path.join(new_src_dir, '\\'.join([nm for nm in fdir.split('\\') if nm not in oldsrc_dirnms]))
        if not os.path.isdir(new_fdir):
            os.makedirs(new_fdir)
        WriteFile(os.path.join(new_fdir, fname+filesuf), soup.prettify())
    return True


def DirUniTagsByName(src_dir, unitags, fnpt=r"", parser_type='lxml-xml', dirsuf="_new", filesuf=""):
    if type(unitags) is not dict or not BoolAND([(type(pn) is str and type(cn) is str) for pn, cn in unitags.items()]):
        print('\033[31m%s\033[0m' % "The input of unitags is not correct! ...")
        return False
    # ---- Get directory for storing the new source text ----
    new_src_dir = src_dir + dirsuf
    if not os.path.isdir(new_src_dir):
        os.makedirs(new_src_dir)
    # ---- Get source file path list ----
    fplist = []
    if os.path.isfile(src_dir):
        fplist = [src_dir]
    elif os.path.isdir(src_dir):
        fplist = GetFileDirPaths(src_dir, 3)[0]
    # ---- For each source file, delete tags that are not in tags ----
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(fnpt, fname) is None:
            continue
        print("Unifying tags for", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), parser_type)
        soup = UniTags(soup, unitags)
        # ---- get new file path, and writtern new source files ----
        new_fdir = os.path.join(new_src_dir, fdir.lstrip(src_dir))
        if not os.path.isdir(new_fdir):
            os.makedirs(new_fdir)
        WriteFile(os.path.join(new_fdir, fname+filesuf), soup.prettify())
    return True


def DelNoTagStrings(soup):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.NavigableString, bs4.element.Tag]:
        print("RenameTags: type of the soup is error!")
        return
    for string in soup.strings:
        if string.strip() and string.parent.name == 'body':
            string.extract()
    return soup


def DelAIConcSec(ai_deltags, ai_unitags):
    con_fdir = ai_fdir + "_con"
    success_flag = DirDelTagsByName(ai_fdir, ai_deltags, ai_fnpt, dirsuf="_con", filesuf=".C")
    success_flag = success_flag and DirUniTagsByName(con_fdir, ai_unitags, ai_fnpt, dirsuf="")
    if not success_flag:
        return
    fplist, dirlist = GetFileDirPaths(con_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(ai_fnpt, fname) is None:
            continue
        print("Deleting Conclusion Section from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
        conc_tag = None
        for cur_title in soup.find_all("section-title")[::-1]:
            if re.search("conclusion", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("concluding", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("summary", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("discussion", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("remarks", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            if conc_tag is not None:
                break
        if conc_tag is None:
            print(fname, "has no Conclusion section, Delete this file!")
            os.remove(fp)
        else:
            conc_tag.extract()
            WriteFile(fp, soup.prettify())
    return


def DelAIIntroSec(ai_deltags, ai_unitags):
    int_fdir = ai_fdir + "_int"
    success_flag = DirDelTagsByName(ai_fdir, ai_deltags, ai_fnpt, dirsuf="_int", filesuf=".I")
    success_flag = success_flag and DirUniTagsByName(int_fdir, ai_unitags, ai_fnpt, dirsuf="")
    if not success_flag:
        return
    fplist, dirlist = GetFileDirPaths(int_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(ai_fnpt, fname) is None:
            continue
        print("Deleting Introduction section from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
        intro_tag = None
        for cur_title in soup.find_all("section-title"):
            if re.search("introduction", cur_title.string, flags=re.IGNORECASE):
                intro_tag = cur_title.parent
            if intro_tag is not None:
                break
        if intro_tag is None:
            print(fname, "has no Introduction, delete this file!")
            os.remove(fp)
        else:
            intro_tag.extract()
            WriteFile(fp, soup.prettify())
    return


def DelACLSec(con_fdir, del_sectitle, parser_type='lxml'):
    fplist, dirlist = GetFileDirPaths(con_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(acl_fnpt, fname) is None:
            continue
        print("Deleting", del_sectitle, "Section from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), parser_type)
        del_sectag = None
        for cur_div in soup.find_all("div")[::-1]:
            if 'class' not in cur_div.attrs or "ltx_section" not in cur_div['class'] or not cur_div.h2:
                continue
            sectitle_str = ' '.join(cur_div.h2.stripped_strings)
            if re.match(del_sectitle, sectitle_str, flags=re.IGNORECASE):
                del_sectag = cur_div
                break
        if not del_sectag:
            print(fname, "has no such a section")
        else:
            del_sectag.extract()
            WriteFile(fp, soup.prettify())
    return


def CheckSentNumWordNumInSummary(sum_fdir, sum_fnpt):
    for sum_fn in GetFileNameList(sum_fdir):
        if not re.match(sum_fnpt, sum_fn):
            continue
        soup = BeautifulSoup(ReadFile(os.path.join(sum_fdir, sum_fn)), "lxml")
        sent_tags = [tag for tag in soup.find_all('a') if "href" in tag.attrs]
        word_num = 0
        for tag in sent_tags:
            sent = re.sub('\s+', ' ', tag.getText().strip())
            word_num += len(sent.split(' '))
        meta_content_str = "SENT_NUM: "+str(len(sent_tags)) + ", WORD_NUM: "+str(word_num)

        if not soup.meta:
            if not soup.head:
                soup.insert(0, soup.new_tag("head"))
            print("New \'meta\' tag in \'head\' tag  -->", meta_content_str)
            soup.head.append(soup.new_tag('meta', content=meta_content_str))
        else:
            print(sum_fn+": ", soup.meta["content"], "-->", meta_content_str)
            soup.meta["content"] = "SENT_NUM: "+str(len(sent_tags)) + ", WORD_NUM: "+str(word_num)

        WriteFile(os.path.join(sum_fdir, sum_fn), str(soup))


def AddCommaInSummaries(sum_dir=acl_fsdir['mrk'][1], sum_fnpt=acl_snpt):
    for sname in GetFileNameList(sum_dir):
        if not re.match(sum_fnpt, sname, flags=re.IGNORECASE):
            continue
        sfp = os.path.join(sum_dir, sname)
        fstring = ReadFile(sfp)
        soup = BeautifulSoup(fstring, 'lxml')
        topsent = []
        for a in soup.find_all('a'):
            if u'id' in a.attrs:
                sent = (a.string[0].upper() + a.string[1:]).rstrip('.')+'.'
                topsent.append(sent)
        WriteFile(sfp, ProduceSummaryHTML(topsent, formatsent=1))


def AddCommaInSrcTitle(src_dir, src_fnpt=r".+"):
    fplist, dplist = GetFileDirPaths(src_dir, depth=2)
    for idx, fp in enumerate(fplist):
        if not re.match(src_fnpt, os.path.basename(fp), flags=re.IGNORECASE):
            continue
        print(idx, ": add a comma to the title of", os.path.basename(fp), "...")
        soup = BeautifulSoup(ReadFile(fp), 'lxml')
        soup.title.string = soup.title.string.strip().rstrip('.') + '.'
        WriteFile(fp, soup.prettify())


def CommaInSummaryDifferFromSource(dataset='acl', ftype='abs'):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    src_sum_path_align_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_path_align_dict.keys():
        src_sents = GetSentsList(srcfp)
        src_embs = EmbedSents2Vectors(src_sents)
        for sumfp in src_sum_path_align_dict[srcfp]:
            print("====================================")
            print(os.path.basename(sumfp))
            print("====================================")
            sum_sents = GetSentsList(sumfp)
            sum_embs = EmbedSents2Vectors(sum_sents)
            for sum_sid, emb in enumerate(sum_embs):
                max_src_sid, max_sim = 0, 0.0
                for src_sid, src_emb in enumerate(src_embs):
                    temp_sim = max(float(cosine_similarity(emb, src_emb)), 0.0)
                    if temp_sim > max_sim:
                        max_sim = temp_sim
                        max_src_sid = src_sid
                if src_sents[max_src_sid].strip()[-1] != sum_sents[sum_sid].strip()[-1]:
                    print(sum_sents[sum_sid])
                    print(src_sents[max_src_sid])
                    print("------------------------------")
            print()


#######################################################################################
# -------------------------------- Produce HTML files ------------------------------- #
#######################################################################################
def ProduceSummaryHTML(tops, formatsent=0):
    modeltxt = '''<html>\n<head>\n'''
    # ---- get sentences list ----
    if type(tops) != list:
        if type(tops) != str:
            if formatsent == 1:
                return modeltxt
            else:
                return ""
        tops = sent_tokenizer.tokenize(tops.strip())

    # ---- change sentences into some format ----
    sent_num = len(tops)
    word_num = 0
    bodytxt = ''
    for i, sent in enumerate(tops):
        if not sent:
            continue
        word_num += len(sent.split())
        if formatsent == 1:
            bodytxt += '''<a href="#%d" id="%d">%s</a>\n''' % (i, i, sent)
        if formatsent == 0:
            bodytxt += sent + '\n'

    # ---- if current summary has no content, do not generate the html file ----
    if len(bodytxt.strip()) == 0:
        return bodytxt

    # ---- If the formatsent is True, added the <body> tag in bodytxt----
    if formatsent == 1:
        bodytxt = '''<body bgcolor="white">\n%s</body>\n</html>''' % (bodytxt)

    # ---- Add SENTENCE NUMBER and WORD NUMBER into <meta> of <head> -----
    modeltxt += '''<meta name="TextLength" content="SENT_NUM:%d, WORD_NUM:%d">\n</head>\n''' % (sent_num, word_num)
    if formatsent == 1:
        return modeltxt + bodytxt
    if formatsent == 0:
        return bodytxt


# ---- 将文件中所有形如u'\u2901'的字符串替换为对应的字符 ----
def DecodeUTF8(text):
    text = re.sub(r"\' u\'", "", text)
    wordlist = DelEmptyString(text.split(' '))
    for widx, word in enumerate(wordlist):
        mt = re.match(r"u\'(.+)\'", word)
        if mt is not None:
            try:
                wordlist[widx] = mt.groups()[0].encode('utf-8').decode('unicode_escape')
            except UnicodeEncodeError:
                wordlist[widx] = json.loads(mt.groups()[0])
    return ' '.join(wordlist)


def DecodeTagString(p_tag):
    if type(p_tag) not in [bs4.BeautifulSoup, bs4.element.NavigableString, bs4.element.Tag]:
        return
    if p_tag.string is None:
        for c_tag in p_tag.contents:
            DecodeTagString(c_tag)
    else:
        p_tag.string = DecodeUTF8(p_tag.string)
    return


def DecodeStrsInHtmlFiles(file_dir, namept=r".+", parser_type="lxml"):
    fplist, dplist = GetFileDirPaths(file_dir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(namept, fname) is None:
            continue
        print(r"Decode string like u'\u2013' from html file", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), parser_type)
        DecodeTagString(soup)
        WriteFile(fp, soup.prettify())
    return


def ProduceAIAbsSum():
    fplist, dirlist = GetFileDirPaths(ai_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(ai_fnpt, fname) is None:
            continue
        print("Getting Abstract Summary from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp, 'utf-8'), 'lxml-xml')
        abs_tag = soup.find("abstract")
        if abs_tag is None:
            print("\tNo Abstract section, skip this file!")
            continue
        # ----- Extract Strings and Written Sentence into html file -----
        sents_list = sent_tokenizer.tokenize(abs_tag.string)
        WriteFile(os.path.join(ai_fsdir['abs'][1], fname + '.A.A'), ProduceSummaryHTML(sents_list, formatsent=1))
    return


def ProduceAIConcSum(ai_deltags=[], ai_unitags={}):
    fplist, dirlist = GetFileDirPaths(ai_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(ai_fnpt, fname) is None:
            continue
        print("Getting Conclusion Summary from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
        conc_tag = None
        for cur_title in soup.find_all("section-title")[::-1]:
            if re.search("conclusion", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("concluding", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("summary", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("discussion", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            elif re.search("remarks", cur_title.string, flags=re.IGNORECASE):
                conc_tag = cur_title.parent
            if conc_tag is not None:
                break
        if conc_tag is None:
            print("\tNo Conclusion section, skip this file!")
            continue
        # ----- Delete tags from the con_tag -----
        if ai_deltags:
            conc_tag = DelTags(conc_tag, ai_deltags)
        # ----- Unify the child tags in the con_tag -----
        if ai_unitags:
            conc_tag = UniTags(conc_tag, ai_unitags)
        # ----- Extract Strings and Written Sentence into html file -----
        sents_list = GetSentsForSoup(conc_tag)
        WriteFile(os.path.join(ai_fsdir['con'][1], fname+'.C.B'), ProduceSummaryHTML(sents_list, formatsent=1))
    return


def ProduceAIIntroSum(ai_deltags=[], ai_unitags={}):
    fplist, dirlist = GetFileDirPaths(ai_fdir)
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if re.match(ai_fnpt, fname) is None:
            continue
        print("Getting Introduction Summary from", fname, "...")
        soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
        intro_tag = None
        for cur_title in soup.find_all("section-title"):
            if re.search("introduction", cur_title.string, flags=re.IGNORECASE):
                intro_tag = cur_title.parent
            if intro_tag is not None:
                break
        if intro_tag is None:
            print("\tNo Introduction section, skip this file!")
            continue
        # ----- Delete tags from the intro_tag -----
        if ai_deltags:
            intro_tag = DelTags(intro_tag, ai_deltags)
        # ----- Unify the child tags in the con_tag -----
        if ai_unitags:
            intro_tag = UniTags(intro_tag, ai_unitags)
        # ----- Extract Strings and Written Sentence into html file -----
        sents_list = GetSentsForSoup(intro_tag)
        WriteFile(os.path.join(ai_fsdir['int'][1], fname + '.I.D'), ProduceSummaryHTML(sents_list, formatsent=1))
    return


def ProduceWstSum(dataset='acl', ftype='abs', cache_dtypes=['Sents', 'PTrees', 'SumSLN', 'sumSLNs', 'sumVecs']):
    # ---- just produce worst summary for abstract, conclusion, introduction ----
    if ftype not in ['abs', 'con', 'int']:
        return
    # ---- Get dataset info ----
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    # ---- Check historical worst summary file path align dict ----
    sumfp_pairs_pkfp = os.path.join(pk_dir, ftype+"_wst_fpalign_dict.pk")
    if os.path.isfile(sumfp_pairs_pkfp):
        sumfp_pairs = Loadpickle(sumfp_pairs_pkfp)
    # ---- If no historical cache data, produce the summary-align-pairs by JCD similarity ----
    else:
        # -- get summary file path list --
        src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
        sumfp_list = []
        for srcfp in src_sum_fpalign_dict:
            for sumfp in src_sum_fpalign_dict[srcfp]:
                sumfp_list.append(sumfp)
        # -- calculate the JCD simialrity between each pair of summaries --
        _num = len(sumfp_list)
        sum_jcd_simM = np.zeros(shape=(_num, _num))
        for row_idx in range(_num):
            rowtxt = ' '.join(GetFileCacheDatas(sumfp_list[row_idx], 'Sents', pk_dir))
            for col_idx in range(row_idx+1, _num):
                coltxt = ' '.join(GetFileCacheDatas(sumfp_list[col_idx], 'Sents', pk_dir))
                jcd_sim = jcd_similarity(rowtxt, coltxt, _stopw=True)
                sum_jcd_simM[row_idx, col_idx] = jcd_sim
                sum_jcd_simM[col_idx, row_idx] = jcd_sim
        sum_idx_pairM = np.argsort(sum_jcd_simM)
        sum_jcd_simM = np.sort(sum_jcd_simM)
        # -- pair each summary with a summary that has the less jcd similarity to it --
        sumfp_pairs = {}
        for base_idx in range(_num):
            base_sumfp = sumfp_list[base_idx]
            suit_cmp_sumfps, first_add = {}, None
            for cidx, cmp_idx in enumerate(sum_idx_pairM[base_idx]):
                cmp_sumfp = sumfp_list[cmp_idx]
                if base_idx == cmp_idx or os.path.basename(base_sumfp)[:5] != os.path.basename(cmp_sumfp)[:5]:
                    continue
                if first_add is None:
                    suit_cmp_sumfps[cmp_sumfp] = sum_jcd_simM[base_idx, cidx]
                    first_add = cmp_sumfp
                elif suit_cmp_sumfps[first_add] == sum_jcd_simM[base_idx, cidx]:
                    suit_cmp_sumfps[cmp_sumfp] = sum_jcd_simM[base_idx, cidx]
                else:
                    break
            wst_sumfp = random.choice(list(suit_cmp_sumfps))
            sumfp_pairs[base_sumfp] = (wst_sumfp, suit_cmp_sumfps[wst_sumfp])
        Dumppickle(sumfp_pairs_pkfp, sumfp_pairs)
        # -- write summary jcd matrix into excel file --
        workbook = xlwt.Workbook(encoding='utf-8')
        worksheet = workbook.add_sheet("JCD-sim")
        for col, header in enumerate(['Base Summary', 'Cmp Summary', 'JCD-sim']):
            worksheet.write(0, col, header, xlwt.easyxf('font: bold on'))
        line = 1
        for ridx in range(_num):
            rsumfn = os.path.basename(sumfp_list[ridx])
            for cidx, sumidx in enumerate(sum_idx_pairM[ridx]):
                csumfn = os.path.basename(sumfp_list[sumidx])
                if ridx == sumidx or rsumfn[:5] != csumfn[:5]:
                    continue
                worksheet.write(line, 0, rsumfn)
                worksheet.write(line, 1, csumfn)
                worksheet.write(line, 2, sum_jcd_simM[ridx, cidx])
                line = line + 1
        workbook.save(os.path.join(score_dir, ftype+'_sum_jcdsim.xls'))
    # ---- copy files as the worst summary ----
    wst_sum_dir = os.path.join(os.path.dirname(sum_dir), "Summary_wst" + ftype[0].upper())
    for sumfp in sumfp_pairs:
        wst_org_sumfp, jcd_sim = sumfp_pairs[sumfp]
        wst_sumfn = '.'.join(os.path.basename(sumfp).split('.')[:-1]) + '.W'
        print("Basefn:", os.path.basename(sumfp), "--> Wstfn:", os.path.basename(wst_org_sumfp), "--> As:", wst_sumfn, "--> JDC-sim:", jcd_sim)
        os.popen(' '.join(['copy', wst_org_sumfp, os.path.join(wst_sum_dir, wst_sumfn)]))
        for dtype in cache_dtypes:
            cache_data = GetFileCacheDatas(wst_org_sumfp, dtype, pk_dir, _tab='\t')
            cache_pkfn = '.'.join([wst_sumfn, dtype, 'pk'])
            Dumppickle(os.path.join(pk_dir, cache_pkfn), cache_data)
            print("\t\tCopy to", cache_pkfn)
    return


def ProduceRandSum(dataset='acl', ftype='abs', outfn_suffix='R', chunknum=5):
    if ftype not in ['abs', 'con', 'int', 'p100', 'm100', 'm200']:
        return
    # ---- Get dataset info ----
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
        if dataset == 'duc':
            outdir = os.path.join(os.path.dirname(sum_dir), '_'.join(['Summary', ftype, outfn_suffix]))
        else:
            outdir = os.path.join(os.path.dirname(sum_dir), 'Summary_rnd')
        if not os.path.isdir(outdir):
            os.makedirs(outdir)
    except:
        return
    # ---- produce random summaries for each source text, according to the length of the summary ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        src_sents = GetFileCacheDatas(srcfp, 'Sents', pk_dir)
        src_ptrees = GetFileCacheDatas(srcfp, 'PTrees', pk_dir)
        src_slns = GetFileCacheDatas(srcfp, 'srcSLNs', pk_dir)
        src_vecs = GetFileCacheDatas(srcfp, 'srcVecs', pk_dir)
        # ---- Get the number of sentences or words to restrict the length of the random summary ----
        wordnum = 0
        for sumfp in src_sum_fpalign_dict[srcfp]:
            soup = BeautifulSoup(ReadFile(sumfp), "lxml")
            mt = re.match(r"SENT_NUM: *(\d+), WORD_NUM: *(\d+)", soup.meta["content"])
            wordnum += int(mt.groups()[1])
        wordnum = wordnum / len(src_sum_fpalign_dict[srcfp])
        # ---- Get a random order of the source text sentences -----
        chunk_sentID, srcsnum, ksnum = [], len(src_sents), int(np.ceil(len(src_sents) / chunknum))
        for i in range(chunknum):
            temp_sentID = list(range(ksnum*i, min(srcsnum, ksnum*(i+1))))
            if not temp_sentID:
                break
            random.shuffle(temp_sentID)
            chunk_sentID.append(temp_sentID)
        chunkID = list(range(len(chunk_sentID)))
        # ---- Get the sentence list that need to write into the random summary file ----
        add_wnum, rnd_sents, rnd_ptrees, rnd_slns, stopflag = 0, [], [], [], False
        while not stopflag and len(chunkID) > 0:
            random.shuffle(chunkID)
            for kid in chunkID:
                sid = chunk_sentID[kid].pop(0)
                temp_stxt = re.sub(r"\s+", ' ', src_sents[sid]).strip()
                temp_wn = len(temp_stxt.split(' '))
                if temp_wn + add_wnum > wordnum and temp_wn > (wordnum - add_wnum) * 2:
                    stopflag = True
                    break
                rnd_sents.append(src_sents[sid])
                rnd_ptrees.append(src_ptrees[sid])
                rnd_slns.append(src_slns[sid])
                add_wnum += temp_wn
            kidx = 0
            while kidx < len(chunkID):
                if not chunk_sentID[chunkID[kidx]]:
                    chunkID.pop(kidx)
                else:
                    kidx += 1
        rnd_SLN = MergeSentsSLN(rnd_slns, 'summary')
        rnd_vecs = {key: src_vecs.get(key, None) for key in GetLabelGenreTuples(rnd_SLN)}
        # ---- Generate and store the '.html' type file for the random summary  ----
        if dataset == 'duc':
            if sumtype == 'p':
                outfn = '.'.join([os.path.basename(os.path.dirname(srcfp)), os.path.basename(srcfp), outfn_suffix])
            else:
                outfn = '.'.join([os.path.basename(srcfp), 'M', ftype.lstrip('m'), 'html', outfn_suffix])
        else:
            outfn = '.'.join([os.path.basename(srcfp), outfn_suffix])
        Dumppickle(os.path.join(pk_dir, '.'.join([outfn, 'Sents', 'pk'])), rnd_sents)
        Dumppickle(os.path.join(pk_dir, '.'.join([outfn, 'PTrees', 'pk'])), rnd_ptrees)
        Dumppickle(os.path.join(pk_dir, '.'.join([outfn, 'sumSLNs', 'pk'])), rnd_slns)
        Dumppickle(os.path.join(pk_dir, '.'.join([outfn, 'SumSLN', 'pk'])), rnd_SLN)
        Dumppickle(os.path.join(pk_dir, '.'.join([outfn, 'sumVecs', 'pk'])), rnd_vecs)
        WriteFile(os.path.join(outdir, outfn), ProduceSummaryHTML(rnd_sents, formatsent=1))
    return


#######################################################################################
# ---------------------------------- Test function ---------------------------------- #
#######################################################################################
def TestDelACLTags():
    # The tag information to filter the source xml/html files in ACL dataset.
    #   1. acl_deltags: the tags needed to be delete from the source xml/html file.
    #   2. acl_strtags: the tags needed to be convert to a string.
    # Each element in these two dict is like:
    #  tag_name: {attr1_name:{string1, string2, string 3}, attr2_name:{string4, string5}}
    # # ------ Source Text has no abstract --------
    # acl_deltags = {
    #     'meta': {}, 'br': {},
    #     'link': {'rel': {'stylesheet'}},
    #     'div': {'class': {'ltx_page_footer', 'ltx_page_logo', 'ltx_role_creation', 'ltx_role_newpage',
    #                       'ltx_authors', 'ltx_date', 'ltx_figure', 'ltx_table', 'ltx_abstract'},
    #             'id': {"Sx1", "bib"}
    #             },
    #     'span': {'class': {'ltx_creator', 'ltx_role_author', 'ltx_personname', 'ltx_ERROR', 'undefined', 'ltx_note'}},
    #     'h1': {'class': {'ltx_title_document'}}
    # }
    # acl_strtags = {
    #     'em': {}, 'a': {}, 'math': {}, 'mo': {}, 'mi': {}, 'mtext': {}, 'mrow': {},
    #     'cite': {'class': {'ltx_cite'}},
    #     'span': {'class': {'ltx_text'}},
    #     'table': {'class': {'ltx_equation'}}
    # }
    # DirIterDelTags(acl_noabs_fdir, acl_deltags, acl_strtags, fnpt=acl_fnpt)
    # AddCommaInSrcTitle(acl_noabs_fdir, acl_fnpt)

    # # ------ Source Text has no conclusion --------
    # acl_deltags = {
    #     'meta': {}, 'br': {},
    #     'link': {'rel': {'stylesheet'}},
    #     'div': {'class': {'ltx_page_footer', 'ltx_page_logo', 'ltx_role_creation', 'ltx_role_newpage',
    #                       'ltx_authors', 'ltx_date', 'ltx_figure', 'ltx_table'},
    #             'id': {"Sx1", "bib"}
    #             },
    #     'span': {'class': {'ltx_creator', 'ltx_role_author', 'ltx_personname', 'ltx_ERROR', 'undefined', 'ltx_note'}},
    #     'h1': {'class': {'ltx_title_document'}}
    # }
    # DirIterDelTags(acl_nocon_fdir, acl_deltags, acl_strtags, fnpt=acl_fnpt)
    # AddCommaInSrcTitle(acl_nocon_fdir, acl_fnpt)
    # DelACLSec(acl_nocon_fdir, r"\d+ +conclusion")

    sum_deltags = {'title': {}, 'a': {'name': set()}}
    # DirIterDelTags(acl_abs_sdir, sum_deltags, {}, fnpt=acl_snpt)
    # DirIterDelTags(acl_con_sdir, sum_deltags, {}, fnpt=acl_snpt)
    DirIterDelTags(os.path.join(acl_dataset, "Summary_cmpA"), sum_deltags, {}, fnpt=acl_snpt)
    DirIterDelTags(os.path.join(acl_dataset, "Summary_cmpC"), sum_deltags, {}, fnpt=acl_snpt)


def TestDelAITags():
    # -------- Del Tags in AI Source Text ---------
    ai_deltags = ['url', 'authors', 'keywords', 'acknowledgements', 'references', 'footnote']
    ai_unitags = {'section': 'section-title'}
    DirDelTagsByName(ai_fdir, ai_deltags+["abstract"], ai_fnpt, 'lxml-xml', "_abs", ".A")
    DirUniTagsByName(ai_fdir+"_abs", ai_unitags, ai_fnpt, dirsuf="")
    DelAIConcSec(ai_deltags, ai_unitags)
    DelAIIntroSec(ai_deltags, ai_unitags)
    for sumtype in ['abs', 'con', 'int']:
        AddCommaInSrcTitle(ai_fsdir[sumtype][0], ai_fnpt)
    # -------- Del Tags in AI summaries ------------
    # sum_deltags = {'title': {}, 'a': {'name': set()}}
    # for sumtype in ['abs', 'con', 'int']
    #     DirIterDelTags(ai_fsdir[sumtype][1], sum_deltags, {}, fnpt=ai_snpt)
    # -------- Decode u'\u2013' in raw summary file --------
    # for sumtype in ['abs', 'con', 'int']
    #     DecodeStrsInHtmlFiles(ai_fsdir[sumtype][1], ai_snpt)


def CheckTagsInDUCSrcFile(duc_fdir):
    fplist, dplist = GetFileDirPaths(duc_fdir, depth=3)
    ftype_tagname_dict = {}
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        cur_ftype = fname[:3]
        soup = BeautifulSoup(ReadFile(fp), 'lxml')
        if cur_ftype not in ftype_tagname_dict:
            ftype_tagname_dict[cur_ftype] = set()
        for tag in soup.descendants:
            if tag.name is not None and tag.name not in ftype_tagname_dict[cur_ftype]:
                ftype_tagname_dict[cur_ftype].add(tag.name)
                print("------------------------")
                print(tag.name, ": New Tag Name for: ", cur_ftype)
                print(fp)
    for ftype in ftype_tagname_dict:
        print("==========================")
        print("File Type:", ftype)
        print("Tags:")
        for tagname in ftype_tagname_dict[ftype]:
            print(tagname, end='\t')
        print()


def DelDUCRepeatSingleSum():
    fp = r"F:\Programs\Eclipse\ReadabilityRating\DUC-Dataset\ScoreTables\Summary_p100_align_info.xml"
    fstring = ReadFile(fp)
    soup = BeautifulSoup(fstring, 'lxml-xml')
    align_list = soup.find_all("ALIGN")
    for align_item in align_list:
        srcfname = align_item.find("SOURCE-FNAME")
        sum_list = align_item.find_all("SUM")
        if len(sum_list) <= 16:
            continue
        print("==== Processing Summary for Source File:", srcfname, " ====")
        sumfp_dict = {}
        for one_sum in sum_list:
            sumroot = one_sum.find("SUMMARY-ROOT").string
            sumfn = one_sum.find("SUMMARY-FNAME").string
            fnkey = '.'.join(sumfn.split('.')[1:])
            if fnkey not in sumfp_dict:
                sumfp_dict[fnkey] = [os.path.join(sumroot, sumfn)]
            else:
                sumfp_dict[fnkey].append(os.path.join(sumroot, sumfn))
        for fnkey, fplist in sumfp_dict.items():
            if len(fplist) < 2:
                continue
            # print("========", fnkey, "=========")
            print(fnkey, fplist)
            # back_fp = fplist[0]
            # back_fstring = "\n".join(ReadFile(back_fp).strip().split("\n")[5:-2])
            # # print("-----", os.path.basename(back_fp), "------")
            # # print(back_fstring)
            # for sumfp in fplist[1:]:
            #     if not os.path.isfile(sumfp):
            #         continue
            #     new_fstring = "\n".join(ReadFile(sumfp).strip().split("\n")[5:-2])
            #     if back_fstring == new_fstring:
            #         print("delete", os.path.basename(sumfp))
            #         os.remove(sumfp)


def TestDelDUCTags(fdir, fnpt, sdir, snpt):
    # ======== Output all tags in DUC source text =============
    # CheckTagsInDUCSrcFile(fdir)
    # ======== Delete unuseful tags ============
    # deltags = ['SECTION', 'PROFILE', 'LANGUAGE', 'PG.COL', 'RE', 'MONTH', 'COUNTRY', 'PUBYEAR', 'DATE1', 'DESCRIPT',
    #            'LENGTH', 'AU', 'GV', 'IN', 'HEADER', 'CITY', 'NOTE', 'MS', 'DOCID', 'CN', 'TYPE', 'DATELINE',
    #            'SECOND', 'DAY', 'F', 'CODE', 'PUBDATE', 'COPYRGHT', 'CO', 'DD', 'SUBJECT', 'TABLE', 'XX', 'REGION',
    #            'EDITION', 'ROWRULE', 'FILEID', 'FIRST', 'CELLRULE', 'SO', 'DATE', 'WORD.CT', 'NS', 'NAME', 'TABLEROW',
    #            'HT', 'TABLECELL', 'MEMO', 'FEATURE', 'G', 'STATE', 'PAGE', 'TP', 'AN', 'BYLINE', 'LIMLEN', 'PHRASE',
    #            'ACCESS', 'PUB', 'DOCNO', 'DOCTYPE', 'AUTHOR', 'DATE_TIME', 'CATEGORY', 'TRAILER', 'SLUG']
    # DirDelTagsByName(fdir, deltags, fnpt, 'lxml-xml')
    # ======== Rename some useful tags ============
    # rename_dict = {'HEAD': 'title', 'HEADLINE': 'title', 'HL': 'title', 'H3': 'title', 'H4': 'title',
    #                'TEXT': 'text', 'GRAPHIC': 'graphic', 'LP': 'leadpara', 'LEADPARA': 'leadpara',
    #                'CAPTION': 'caption', 'TI': 'p', 'P': 'p', 'DOC': 'doc', 'BODY':'body'}
    # for fp in GetFileDirPaths(fdir + "_new", 3)[0]:
    #     fdir, fname = os.path.split(fp)
    #     if re.match(fnpt, fname) is None:
    #         continue
    #     print("Renaming tags for", fname, "...")
    #     soup = RenameTags(BeautifulSoup(ReadFile(fp), 'lxml-xml'), rename_dict)
    #     WriteFile(fp, soup.prettify())
    # ======== Delete no-tag string ========
    for fp in GetFileDirPaths(fdir + "_new", 3)[0]:
        fdir, fname = os.path.split(fp)
        if re.match(fnpt, fname) is None:
            continue
        print("Deleting no tag strings for ", fname, "...")
        soup = DelNoTagStrings(BeautifulSoup(ReadFile(fp), 'lxml-xml'))
        WriteFile(fp, soup.prettify())
    # ======= Find no title ======
    # for fp in GetFileDirPaths(fdir + "_new", 3)[0]:
    #     fdir, fname = os.path.split(fp)
    #     if re.match(fnpt, fname) is None:
    #         continue
    #     soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
    #     if not soup.title or not soup.title.string.strip():
    #         print("No title in", fp)
    # ======== Process files that has more than one title ============
    # err_title_pts = ["^Eds: ", "^Laser([Gg]raph|[Mm]ap|[Pp]hoto|[Cc]olor)", "^With (PM|AM)-", "^\$[Aa]dv",
    #                  "^For Release ", "^(An|From) AP ", "By [A-Z ]+$"]
    # for fp in GetFileDirPaths(fdir+"_new", 3)[0]:
    #     if re.match(duc_fnpt, os.path.split(fp)[1]) is None:
    #         continue
    #     soup = BeautifulSoup(ReadFile(fp), 'lxml-xml')
    #     title_tags = soup.find_all('title')
    #     if len(title_tags) == 1:
    #         title_tags[0].string = re.sub(";; ", "; ", title_tags[0].string)
    #         title_tags[0].string = re.sub("\?\.", "?", title_tags[0].string)
    #         WriteFile(fp, soup.prettify())
    #         continue
    #     # ---- Output the file info that has no title ----
    #     if not title_tags:
    #         print(fp, "No title")
    #         continue
    #     # ---- For the file has multiple titles ----
    #     print(fp, len(title_tags), "titles")
    #     for ttag in title_tags:
    #         # -- skip the title contians more than one sub-tag ----
    #         if ttag.string is None:
    #             continue
    #         # -- check each title to delete the error title --
    #         ttxt = ttag.string.strip()
    #         delflag = ttxt.isupper()
    #         for tpt in err_title_pts:
    #             if delflag:
    #                 break
    #             delflag = delflag or (re.match(tpt, ttxt) is not None)
    #         if delflag:
    #             print("\tdelete title:", ttxt[:10])
    #             ttag.extract()
    #     # -- Merge multiple titles --
    #     if len(soup.find_all('title')) > 1:
    #         print("\tMerge all titles into one!")
    #         MergeTags(soup, ['title'], mrgstr="; ")
    #     WriteFile(fp, soup.prettify())

    # # ======== Add Comma at the end of each title string =========
    # # AddCommaInSrcTitle(duc_fdir, duc_fnpt)
    #
    # # ======== Delete Useless Tags in each summary =========
    # DirIterDelTags(sdir, {'title': {}, 'a': {'name': set()}}, {}, fnpt=snpt)


def CountsWordsInSrcSum(srcdir, sumdir, pkdir, srcfnpt=r".+", sumfnpt=r".+", sumtype="p"):
    src_sum_fpalign_dict = AlignSrcSum(srcdir, sumdir, srcfnpt, sumfnpt, sumtype)
    total_src_wnum = 0.0
    total_src_fnum = len(src_sum_fpalign_dict)
    total_sum_wnum = 0.0
    total_sum_fnum = 0.0
    for srcfp in src_sum_fpalign_dict:
        sents_list = GetFileCacheDatas(srcfp, 'Sents', pkdir)
        for stxt in sents_list:
            total_src_wnum += len(nltk.word_tokenize(stxt))
        total_sum_fnum += len(src_sum_fpalign_dict[srcfp])
        for sumfp in src_sum_fpalign_dict[srcfp]:
            sents_list = GetFileCacheDatas(sumfp, 'Sents', pkdir)
            for stxt in sents_list:
                total_sum_wnum += len(nltk.word_tokenize(stxt))
    print(total_src_wnum/total_src_fnum, total_sum_wnum/total_sum_fnum)


def FindLongestPaper(srcdir, pkdir, srcfnpt=r".+"):
    srcfplist = GetFileDirPaths(srcdir, depth=3)[0]
    max_paper, max_snum, max_wnum = None, 0, 0
    for srcfp in srcfplist:
        wnum, sents_list = 0, GetFileCacheDatas(srcfp, 'Sents', pkdir)
        for stxt in sents_list:
            wnum += len(nltk.word_tokenize(stxt))
        if wnum > max_wnum:
            max_wnum = wnum
            max_snum = len(sents_list)
            max_paper = srcfp
    print(os.path.basename(max_paper))
    print("Words:", max_wnum)
    print("Sents:", max_snum)


def PutFileIntoSubDir(dirfp, fnpt):
    fplist = GetFileDirPaths(dirfp, depth=1)[0]
    file_count = 0
    for fp in fplist:
        fname = os.path.basename(fp)
        if re.match(fnpt, fname):
            file_count += 1
            subdirfp = os.path.join(dirfp, fname.split('.')[0])
            if not os.path.isdir(subdirfp):
                os.mkdir(subdirfp)
            shutil.move(fp, subdirfp)
    print(file_count, "files has been moved into sub-directories")


def CopyFileIntoDir(dirfp, fnpt):
    fplist = GetFileDirPaths(dirfp, depth=3)[0]
    for fp in fplist:
        fname = os.path.basename(fp)
        if re.match(fnpt, fname):
            print("Copy", fname, "...")
            shutil.copy(fp, os.path.join(dirfp, fname))


def ChangeSentsIntoSum(dirfp, fnpt):
    fplist = GetFileDirPaths(dirfp)[0]
    for fp in fplist:
        fdir, fname = os.path.split(fp)
        if not re.match(fnpt, fname):
            continue
        sent_list = DelEmptyString([sent.strip() for sent in ReadFile(fp, codetype='utf-8').split('\n')])
        if not sent_list:
            print(fname, "has no sentences!")
        if len(sent_list) == 1:
            sent_list = DelEmptyString([sent.strip() for sent in sent_list[0].split('. . .')])
            sent_list = [sent+'.' for sent in sent_list]
        html_txt = ProduceSummaryHTML(sent_list, formatsent=1)
        WriteFile(fp, html_txt)


#######################################################################################
# ---------------------------------- Main function ---------------------------------- #
#######################################################################################
if __name__ == "__main__":
    # CommaInSummaryDifferFromSource()
    # AddCommaInSummaries(ai_fsdir['sysC'][1], ai_snpt)
    # CheckSentNumWordNumInSummary(os.path.join(acl_dataset, "Summary_std"), acl_std_snpt)
    # DelDUCRepeatSingleSum()
    # TestDelDUCTags()
    # TestDelACLTags()
    # TestDelAITags()
    # ProduceAIAbsSum()
    # ProduceAIConcSum(ai_deltags=['section-title'])
    # ProduceAIIntroSum(ai_deltags=['section-title'])
    # ProduceWstSum(dataset='ai', ftype='abs', cache_dtypes=[])
    # CountsWordsInSrcSum(duc_fsdir['p100'][0], duc_fsdir['p100'][1], duc_pkdir, duc_fnpt, duc_psnpt)
    # for sumdir in [duc_m10_sdir, duc_m50_sdir, duc_m100_sdir, duc_m200_sdir]:
    #     CountsWordsInSrcSum(duc_fdir, sumdir, duc_pkdir, duc_dirnpt, duc_msnpt, sumtype='m')
    # FindLongestPaper(ai_fsdir['abs'][0], ai_pkdir)
    # PutFileIntoSubDir(r"F:\Programs\Eclipse\DUC Dataset Collections\DUC2007\peer_summ", r"D[0-9]{4}\.M\.250\.[A-Z]\.[0-9]+")
    # CopyFileIntoDir(r"F:\Programs\Eclipse\ReadabilityRating\QRY-Dataset\SummaryFiles", qry_snpt)
    # TestDelDUCTags(r"F:\Programs\Eclipse\ReadabilityRating\QRY-Dataset\SourceFiles_temp", r"^([A-Z]{3}[0-9]{8}\.[0-9]{4})$", qry_sys_sdir, qry_sys_snpt)
    # ChangeSentsIntoSum(qry_sys_sdir, r"D[0-9]{4}\.M\.250\.[A-Z]\.[0-9]+")
    CheckSentNumWordNumInSummary(r"F:\Programs\Eclipse\ReadabilityRating\ACL-Dataset\Summary_wst", acl_snpt)
    # DecodeStrsInHtmlFiles(os.path.join(acl_dataset, "Summary_cmpA"), acl_snpt)
    # ProduceRandSum('duc', 'p100', outfn_suffix='R')
    # ProduceRandSum('duc', 'm100', outfn_suffix='R')
    # ProduceRandSum('duc', 'm200', outfn_suffix='R')