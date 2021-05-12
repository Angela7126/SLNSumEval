# -*- coding: UTF-8 -*-

#######################################################################################
# ---------------------------------- Global variable -------------------------------- #
#######################################################################################
import nltk
import math
import numpy as np
import copy
import bs4
from Utilities import *
from collections import Counter
from bs4 import BeautifulSoup
from nltk.tokenize.punkt import PunktSentenceTokenizer, PunktParameters
from nltk.corpus import words
from nltk.tree import *
from nltk.translate.bleu_score import sentence_bleu, SmoothingFunction
from nltk.stem.porter import PorterStemmer
import itertools
from stanfordcorenlp import StanfordCoreNLP
import gensim
import json
from gensim.scripts.glove2word2vec import glove2word2vec
from sklearn.metrics.pairwise import cosine_similarity
from sklearn.decomposition import TruncatedSVD
from nltk.stem import WordNetLemmatizer
import networkx as nx
import matplotlib.pyplot as plt
import time
import gc
import en_core_web_sm
import neuralcoref

# ----- punctuations and words in English ------
EN_words = set(words.words())
RemoveWords = set(Loadpickle(os.path.join(corpus_dir, 'StopWPuncs.pk')))
Full_stop = ['.', '?', '!', '--', ':', '。', '——', '？', '！', '…', '：']
Puncs = [',', '.', ':', ';', '?', '!', '&', '*', '@', '#', '$', '%', '-', '+', '=', '\'', '\"', '|', '~', '^',
         '’', '”', '`', '``', '--', '\r', '\n', '\t', '\\', '/', '(', ')', '[', ']', '{', '}', '<', '>', '∪',
         '∩', '←', '↑', '→', '↓', '，', '。', '：', '；', '（', '）', '“', '”', '【', '】', '——', '？', '！',
         '‘', '《', '》', '…', '、']
# ---- pos-map maps the NLTK pos-tag into lemmatizer's pos-tag ----
pos_map = {'JJR': 's', 'JJS': 's', 'RBR': 's', 'RBS': 's', 'NN': 'n', 'RB': 'r', 'JJ': 'a', 'VB': 'v', 'MD': 'v'}
lemma = WordNetLemmatizer()
porter_stemmer = PorterStemmer()
# ---- sent_tokenizer to split text into sentences and skip abbreviation ----
punkt_param = PunktParameters()
paper_abbrev_set = {'i.e', 'e.g', 'fig', 'al', 'vs', 'no'}
duc_abbrev_set = {'i.e', 'e.g', 'fig', 'al', 'vs', 'no',
                  'jan', 'feb', 'mar', 'apr', 'may', 'jun', 'jul', 'aug', 'sept', 'oct', 'nov', 'dec', 'a.m', 'p.m',
                  'ca', 'u.n', 'u.k', 'u.s', 'w.va', 'gov', 'cos', 'co', 'corp', 'inc', 'ltd',
                  'mr', 'mrs', 'col', 'cmdr', 'rev', 'sen', 'sens', 'rep', 'maj', 'adm', 'sgt', 'capt', 'dr', 'drs',
                  'dist', 'atty', 'rev', 'ste', 'st', 'lt', 'rt', 'ms', 'ch', 'ens', 'jr', 'm.a', 'ph.d',
                  'a.s', 'b.b', 'e.p', 'f.w', 'g.i', 'h.s', 'h.n', 'j.c', 'j.g', 'l.a', 'l.c', 'l.m',
                  'm.l', 'm.v', 'm.k', 'n.y', 'p.o', 'p.w', 'p.k', 'r.s',  'r.n', 'r.d', 'r-n', 'r-ind',
                  's.c', 's.f', 's.o.b', 'v.p', 'w.h', 'w.l'}
punkt_param.abbrev_types = duc_abbrev_set
sent_tokenizer = PunktSentenceTokenizer(punkt_param)

# ----- initiate CoreNLP parser -------
corenlp = None
# try:
#     corenlp = StanfordCoreNLP(coreNLP_path, memory='4g')
# except:
#     corenlp = None
#     pass

# -- for coreference resolution --
nlp = en_core_web_sm.load()
neuralcoref.add_to_pipe(nlp)

# # -- Convert the GloVe Word2Vec text into Binary Type, Run First! --
# glove2word2vec(os.path.join(corpus_dir, "glove.840B.300d.txt"), os.path.join(corpus_dir, "glove.840B.300d.w2v.txt"))
word_vector, wiki_wordfreq, wiki_wordTFIDF = {}, {}, {}

# # ---- Load "glove" need 843 seconds ----
# print('\033[33m%s\033[0m' % 'Load Word Vectors ...')
# word_vector = gensim.models.KeyedVectors.load_word2vec_format(os.path.join(corpus_dir, "glove.840B.300d.w2v.txt"))
# # --- load "google_news" need 76 seconds ---
# # word_vector = gensim.models.KeyedVectors.load_word2vec_format(os.path.join(corpus_dir, "GoogleNews-neg300.bin"), binary=True)
# # ---- Load Words Frequency in Wikipedia documents, 4s ----
# print('\033[33m%s\033[0m' % 'Load Word Frequency collected from Wikipedia corpus ...')
# wiki_wordfreq = ReadTSV(os.path.join(corpus_dir, "wiki_wordfreq.tsv"))
# # ---- Load Word TFIDF in Wikipedia documents, 4s ----
# print('\033[33m%s\033[0m' % 'Load Word TFIDF collected from Wikipedia corpus ...')
# wiki_wordTFIDF = ReadTSV(os.path.join(corpus_dir, "wiki_wordTFIDF.tsv"))
# wiki_wordTFIDF["NUM_DOCS"] = 1288431


#######################################################################################
# ------------------------ Align Summaries Files and Files  ------------------------- #
#######################################################################################
def WriteAlignFileSumXML(src_sum_fpalign_dict, align_xml_fp):
    print("Write Source-Summary Align File", align_xml_fp, "...")
    src_fplist = sorted([fp for fp in src_sum_fpalign_dict.keys()])
    bodytxt = "<SOURCE-SUMMARY-ALIGN>\n"
    for idx, srcfp in enumerate(src_fplist):
        sum_fplist = src_sum_fpalign_dict[srcfp]
        if len(sum_fplist) == 0:
            continue
        bodytxt += '\t<ALIGN ID=\"%d\">\n' % (idx + 1)
        bodytxt += '\t\t<SOURCE-ROOT>%s</SOURCE-ROOT>\n' % os.path.dirname(srcfp)
        bodytxt += '\t\t<SOURCE-FNAME>%s</SOURCE-FNAME>\n' % os.path.basename(srcfp)
        bodytxt += '\t\t<SUMMARIES>\n'
        for sidx, sumfp in enumerate(sum_fplist):
            bodytxt += '\t\t\t<SUM ID=\"%d\">\n' % (sidx + 1)
            bodytxt += '\t\t\t\t<SUMMARY-ROOT>%s</SUMMARY-ROOT>\n' % os.path.dirname(sumfp)
            bodytxt += '\t\t\t\t<SUMMARY-FNAME>%s</SUMMARY-FNAME>\n' % os.path.basename(sumfp)
            bodytxt += '\t\t\t</SUM>\n'
        bodytxt += '\t\t</SUMMARIES>\n'
        bodytxt += '\t</ALIGN>\n\n'
    bodytxt += '</SOURCE-SUMMARY-ALIGN>'
    WriteFile(align_xml_fp, bodytxt)
    return


# ==== AlignSrcSum: align each summary path to its source file path ====
# src_dir: the directory path to store the source files
# sum_dir: the directory path to store the summary files
# src_npt: the file name pattern of the source files
# sum_npt: the file name pattern of the summary files
# sumtype: 'p' is single-document summary; 'm' is multi-document summary
def AlignSrcSum(src_dir, sum_dir, src_npt=r'.+', sum_npt=r'.+', sumtype='p'):
    src_fplist = []
    sum_fplist = []
    src_sum_fpalign_dict = {}
    # ---- If src_dir is a file ----
    if os.path.isfile(src_dir):
        src_fplist = [src_dir]
    # ---- If files_path is a directory ----
    elif os.path.isdir(src_dir):
        fplist, dplist = GetFileDirPaths(src_dir, depth=2)
        check_fplist = fplist
        if sumtype == 'm':
            check_fplist = dplist
        for srcfp in check_fplist:
            if re.match(src_npt, os.path.basename(srcfp), flags=re.IGNORECASE):
                src_fplist.append(srcfp)
    else:
        print('\033[31m%s\033[0m' % 'Error! Not source files are given!')
    # ---- If sums_path is a file ----
    if os.path.isfile(sum_dir):
        sum_fplist = [sum_dir]
    # ---- If sums_path is a directory ----
    elif os.path.isdir(sum_dir):
        fplist, dplist = GetFileDirPaths(sum_dir, depth=2)
        for sumfp in fplist:
            if re.match(sum_npt, os.path.basename(sumfp), flags=re.IGNORECASE):
                sum_fplist.append(sumfp)
    else:
        print('\033[31m%s\033[0m' % 'Error! Not summary files are given!')
    # ---- If both files_path and sums_path are all single file ----
    if len(src_fplist) == 1 and len(sum_fplist) == 1:
        src_sum_fpalign_dict = {src_fplist[0]: sum_fplist[0]}
    # ---- Align each file with its summaries ----
    elif len(src_fplist) > 1 or len(sum_fplist) > 1:
        for fp in src_fplist:
            temp_splist = []
            srcmt = re.match(src_npt, os.path.basename(fp), flags=re.IGNORECASE)
            for sp in sum_fplist:
                summt = re.match(sum_npt, os.path.basename(sp), flags=re.IGNORECASE)
                if re.match(srcmt.group(), summt.group(), flags=re.IGNORECASE):
                    temp_splist.append(sp)
                elif srcmt.groups() and summt.groups() and set(srcmt.groups()).issubset(set(summt.groups())):
                    temp_splist.append(sp)
            # ---- Store summary fplist to the source file if the list is not empty ----
            if temp_splist:
                src_sum_fpalign_dict[fp] = temp_splist
    return src_sum_fpalign_dict


# ---- Get File Path list -----
def GetFplist(dirfp, ftype, fnpt=r"", depth=2):
    fplist = []
    if os.path.isfile(dirfp):
        fplist.append(dirfp)
    elif os.path.isdir(dirfp):
        fps, dps = GetFileDirPaths(dirfp, depth=depth)
        for fp in dps if ftype == 'm' else fps:
            if re.match(fnpt, os.path.basename(fp), flags=re.IGNORECASE):
                fplist.append(fp)
    else:
        print('\033[31m%s\033[0m' % 'Error! Not source files are given!')
    return fplist


#######################################################################################
# ------------------------- Get sentences list for each file ------------------------ #
#######################################################################################
def SplitTitleSent(title_txt):
    if not isinstance(title_txt, str):
        return []
    title_txt = title_txt.strip()
    title_txt = re.sub("\s+", " ", title_txt)
    return sent_tokenizer.tokenize(title_txt)


def GetSrcTitle(srcfpath, _tab=""):
    # ----- Check the type of the File -----
    (ftype_prefix, ftype) = os.path.splitext(srcfpath)
    while ftype not in ['.txt', '.xml', '.html', '.xhtml', '']:
        (ftype_prefix, ftype) = os.path.splitext(ftype_prefix)
    if ftype == '':
        print(_tab + '\033[31m%s\033[0m' % 'Error! The file_type not in [.txt, .xml, .html, .xhtml], cannot be handle!')
        return [], None
    # ---- Read the content of the file ----
    fstring = ReadFile(srcfpath)
    # ---- For .txt type file, assume the first sentence is the title ----
    print(_tab + '\033[34m%s\033[0m' % 'Getting title for the file: ' + os.path.basename(srcfpath))
    if ftype == '.txt':
        texts_list = re.split(r'\*~\*#\*~\*', re.sub(r'(\r\n){2,}|(\n){2,}', '*~*#*~*', fstring))
        if len(texts_list) > 0:
            return SplitTitleSent(texts_list[0])
        else:
            return []
    # ---- For .html or .xhtml or .xml file ----
    else:
        parser_type = 'lxml'
        if ftype == '.xml':
            parser_type = 'lxml-xml'
        soup = BeautifulSoup(fstring, parser_type)
        titles = []
        # ---- if the source text contains a tag that is named as <title></title> ----
        if soup.title is not None:
            titles.extend(SplitTitleSent(soup.title.string))
        # ---- if the source text contains a tag that is named as <Title></Title> ----
        elif soup.Title is not None:
            titles.extend(SplitTitleSent(soup.Title.string))
        # ---- if the source text contains a tag that is named as <TITLE></TITLE> ----
        elif soup.TITLE is not None:
            titles.extend(SplitTitleSent(soup.TITLE.string))
        # ---- if no tag named as 'title', check the name and attributes of all tags ----
        else:
            for tag in soup.find_all():
                if tag.name.lower().find("title") >= 0:
                    titles.extend(SplitTitleSent(tag.string))
                else:
                    for attr_name, attr_value in tag.attrs.items():
                        if (attr_name.lower().find("title") >= 0 or attr_value.lower().find(
                                "title") >= 0) and tag.string:
                            titles.extend(SplitTitleSent(tag.string))
                            break
        return titles


# ----- Convert a BeautifulSoup or Tag into a sentence list -----
def GetSentsForSoup(soup):
    if type(soup) not in [bs4.BeautifulSoup, bs4.element.Tag]:
        print("GetSentsForTag: type of the soup is error!")
        return []
    sents_list = []
    for tempstr in soup.stripped_strings:
        tempstr = re.sub(r'\s+', ' ', tempstr)
        tempstr = re.sub(r'- ', '', tempstr).strip()
        # -- skip the empty string --
        if not tempstr:
            continue
        temp_sent_list = sent_tokenizer.tokenize(tempstr)
        # ---- process temporary sentence into final sentences ----
        if not sents_list:
            sents_list.extend(temp_sent_list)
        elif len(temp_sent_list) > 0:
            endword = nltk.word_tokenize(sents_list[-1])[-1]
            firstword = nltk.word_tokenize(temp_sent_list[0])[0]
            # -- if the last-sent in sents_list ends with a full-stop punctuation --
            if endword in Full_stop:
                sents_list.extend(temp_sent_list)
            # -- if the first word starts with a capital letter and is correct, and the last sent is not numbers --
            elif firstword.istitle() and (firstword.lower() in EN_words) and not re.match('\d+(\.\d+)*', endword):
                sents_list.extend(temp_sent_list)
            # -- if the last-sent in sents_list and the first-sent in temp_sent_list are not complete --
            else:
                sents_list[-1] += ' ' + temp_sent_list[0]
                sents_list.extend(temp_sent_list[1:])
    # ---- Strip each sentence ----
    for idx, sent in enumerate(sents_list):
        sents_list[idx] = sent.strip()
    return sents_list


# ----- Convert a html, xml, or txt type article into a sentence list -----
# Suppose that all the source files and summary files are written in English!
def GetSentsList(fpath, _tab=""):
    if not os.path.isfile(fpath):
        print(_tab + '\033[31m%s\033[0m' % 'Error! The path does not point to a file!')
        return []
    # ----- Check the type of the File -----
    (ftype_prefix, ftype) = os.path.splitext(fpath)
    while ftype not in ['.txt', '.xml', '.html', '.xhtml', '']:
        (ftype_prefix, ftype) = os.path.splitext(ftype_prefix)
    if ftype == '':
        print(_tab + '\033[31m%s\033[0m' % 'Error! The file_type not in [.txt, .xml, .html, .xhtml], cannot be handle!')
        return []
    # ----- Read the file ----
    fstring = ReadFile(fpath)
    # ----- Process File to get its sentence list -----
    print(_tab + '\033[34m%s\033[0m' % 'Getting sentences list for the file: ' + os.path.basename(fpath))
    # ---- For .txt type file ----
    if ftype == '.txt':
        texts_list = re.split(r'\*~\*#\*~\*', re.sub(r'(\r\n){2,}|(\n){2,}', '*~*#*~*', fstring))
        for tempstr in texts_list:
            tempstr = re.sub(r'\s+', ' ', tempstr)
            tempstr = re.sub(r'- ', '', tempstr).strip()
            if not tempstr:
                continue
            sents_list = sent_tokenizer.tokenize(tempstr)
            # ---- Strip each sentence ----
            for idx, sent in enumerate(sents_list):
                sents_list[idx] = sent.strip()
            return sents_list
    # ---- For .html or .xhtml or .xml file ----
    else:
        parser_type = 'lxml'
        if ftype == '.xml':
            parser_type = 'lxml-xml'
        soup = BeautifulSoup(fstring, parser_type)
        sents_list = GetSentsForSoup(soup)
        return sents_list


#######################################################################################
# ------------------------------ Sentence Parser Trees ------------------------------ #
#######################################################################################
def SplitSent2Pieces(sent):
    # ----- pre-defined patterns for split sentence string ------
    pattrns = [r'(?<=[^(e\.g|i\.e|al|fig)]\.)\s+', r'(?=e\.g\.)', r'(?=i\.e\.)', r'(?<=\.)(?=[A-Z])',
               r'(?=\(\s*\d+\s*\)\s+[a-zA-Z0-9])', r'(?<=:\s)', r'(?<=;\s)', r'(?<=,\s)']
    # ----- try to use each pattern to split the sentence string ------
    for pt in pattrns:
        pieces = DelEmptyString(re.split(pt, sent))
        if len(pieces) > 1:
            return pieces
    return sent


def GetSingleStanfordPTree(sent):
    if corenlp is None:
        print('\t\033[31m%s\033[0m' % 'Cannot initiate the CoreNLP parser ...')
        return Tree('ROOT', [])
    if type(sent) is not str or not sent.strip():
        print('\t\033[31m%s\033[0m' % 'Cannot Building Stanford-Parser Tree for current type of object ...')
        return Tree('ROOT', [])
    try:
        ptree = Tree.fromstring(corenlp.parse(sent.strip()))
        # print('\t\033[36m%s\033[0m' % 'Building Stanford-Parser Tree for the sentence ...')
        return ptree
    except:
        # ----- Usually occurs json.decoder.JSONDecodeError in very long sentences -----
        # -- split the sentences in pieces by some pre-defined patterns --
        sent_pieces = SplitSent2Pieces(sent)
        if isinstance(sent_pieces, str):
            print('\t\033[31m%s\033[0m' % 'Cannot Building Stanford-Parser Tree, sentence cannot split...')
            return Tree('ROOT', [])
        # -- parse each piece, merge them into one Stanford-Parser tree --
        ptree = Tree('ROOT', [])
        while True:
            err_flag = False
            for pidx, piece in enumerate(sent_pieces):
                try:
                    temp_ptree = Tree.fromstring(corenlp.parse(piece.strip()))
                    if len(temp_ptree) > 0:
                        ptree.extend(temp_ptree[:])
                except:
                    temp_pieces = SplitSent2Pieces(piece)
                    if isinstance(temp_pieces, str):
                        print('\t\033[31m%s\033[0m' % 'Current piece cannot parse and split, skip it ...')
                    else:
                        sent_pieces = temp_pieces + sent_pieces[pidx + 1:]
                        err_flag = True
                        break
            if not err_flag:
                break
        return ptree


# ---- Special Getting a parser-tree for a sentence in AI and ACL dataset ----
def SpecialGetSinglePTree(sent):
    if corenlp is None:
        print('\t\033[31m%s\033[0m' % 'Cannot initiate the CoreNLP parser ...')
        return Tree('ROOT', [])
    if type(sent) is not str or not sent.strip():
        print('\t\033[31m%s\033[0m' % 'Cannot Building Stanford-Parser Tree for current type of object ...')
        return Tree('ROOT', [])
    try:
        ptree = Tree.fromstring(corenlp.parse(sent.strip()))
        # print('\t\033[36m%s\033[0m' % 'Building Stanford-Parser Tree for the sentence ...')
        return ptree
    except:
        # ----- Usually occurs json.decoder.JSONDecodeError in long sentences containing formula -----
        # -- remove '{a mathematical formula}' from the sentence string --
        sent = re.sub("\s+", " ", re.sub("\{a mathematical formula\}", " ", sent)).strip()
        sent = re.sub(",(?!\s)", ", ", sent).strip()
        try:
            ptree = Tree.fromstring(corenlp.parse(sent.strip()))
            return ptree
        # -- split the sentences in pieces by some pre-defined patterns, parse each piece, merge them into one PTree --
        except:
            sent_pieces = SplitSent2Pieces(sent)
            if isinstance(sent_pieces, str):
                print('\t\033[31m%s\033[0m' % 'Cannot Building Stanford-Parser Tree, sentence cannot split...')
                return Tree('ROOT', [])
            ptree = Tree('ROOT', [])
            while True:
                err_flag = False
                for pidx, piece in enumerate(sent_pieces):
                    try:
                        temp_ptree = Tree.fromstring(corenlp.parse(piece.strip()))
                        if len(temp_ptree) > 0:
                            ptree.extend(temp_ptree[:])
                    except:
                        temp_pieces = SplitSent2Pieces(piece)
                        if isinstance(temp_pieces, str):
                            print('\t\033[31m%s\033[0m' % 'Current piece cannot parse and split, skip it ...')
                        else:
                            sent_pieces = temp_pieces + sent_pieces[pidx + 1:]
                            err_flag = True
                            break
                if not err_flag:
                    break
            return ptree


def GetStanfordPTrees(Sents, _tab=""):
    if isinstance(Sents, str):
        if not Sents.strip():
            return Tree('ROOT', [])
        temp_Sents = sent_tokenizer.tokenize(Sents.strip())
        if len(temp_Sents) == 1:
            return GetSingleStanfordPTree(Sents)
        else:
            Sents = temp_Sents
    elif type(Sents) not in [list, tuple, set]:
        print(_tab + '\033[31m%s\033[0m' % 'Cannot Building Stanford-Parser Tree for current type of object ...')
        return Tree('ROOT', [])
    elif corenlp is None:
        print(_tab + '\033[31m%s\033[0m' % 'Cannot initiate the CoreNLP parser ...')
        return [Tree('ROOT', [])] * len(Sents)

    # print('\t\033[36m%s\033[0m' % 'Building Stanford-Parser Trees for the sentence list ...')
    # ----- If the input is a sentence list, for each sentence parse its sentence parser tree ----
    SentPTlst = []
    for sent in Sents:
        if type(sent) is str and sent.strip():
            try:
                SentPTlst.append(GetSingleStanfordPTree(sent))
            except:
                SentPTlst.append(Tree('ROOT', []))
        else:
            SentPTlst.append(Tree('ROOT', []))
    return SentPTlst


#######################################################################################
# ---------------------------------- Theme SLN Class ------------------------------- #
#######################################################################################
class ThemeNode():
    def __init__(self, nid=0, words_tags=None, level=0, times=1):
        self.nid = nid
        self._label = self.process_label(words_tags)
        self.level = level
        self.times = times
        self.merge_nodes = []

    def __eq__(self, b):
        return type(b).__name__ == 'ThemeNode' and self._label == b._label

    def __ne__(self, b):
        return not self.__eq__(b)

    def process_label(self, words_tags):
        if not words_tags:
            return words_tags
        pos_tags = {'NN': 'n', 'RB': 'r', 'JJ': 'a', 'JJR': 's', 'JJS': 's', 'RBR': 's', 'RBS': 's'}
        labels = []
        for word, tag in words_tags:
            word = word.lower()
            if tag in pos_tags:
                labels.append(lemma.lemmatize(word, pos=pos_tags[tag]))
            elif len(tag) > 2 and tag[:2] in pos_tags:
                labels.append(lemma.lemmatize(word, pos=pos_tags[tag[:2]]))
            else:
                labels.append(word)
        return ' '.join(labels)


class ThemeLink():
    def __init__(self, label=None, type=None, level=0, l_node=None, r_node=None, times=1):
        self._label = self.process_label(label, type)
        self._type = type
        self.level = level
        self.l_node = l_node
        self.r_node = r_node
        self.times = times

    def __eq__(self, b):
        equal_flag = (type(b).__name__ == "ThemeLink")
        if equal_flag:
            equal_flag = equal_flag and self._label == b._label and self._type == b._type
            equal_flag = equal_flag and self.l_node == b.l_node
            equal_flag = equal_flag and self.r_node == b.r_node
        return equal_flag

    def __ne__(self, b):
        return not self.__eq__(b)

    def process_label(self, raw_label, link_type):
        if not raw_label:
            return raw_label
        label_words = [w.lower() for w in raw_label.strip().split(' ') if len(w) > 0]
        pos_tags = {'VB': 'v', 'MD': 'v', 'RB': 'r'}
        if link_type in ['VB', 'MD', 'RB']:
            for idx, w in enumerate(label_words):
                label_words[idx] = lemma.lemmatize(w, pos=pos_tags[link_type])
        return ' '.join(label_words)


class ThemeSLN():
    def __init__(self, Nodes, Links, type='sent'):
        self.type = type
        # ----- Add Nodes into Theme SLN -----
        for idx, node in enumerate(Nodes):
            node.nid = idx
        self.Nodes = Nodes
        # ----- Add Links into Theme SLN -----
        self.Links = []
        link_info2idx_map = {}
        for link in Links:
            # ----- ignore links that cannot be linked to two nodes -----
            if link.l_node is None or link.r_node is None:
                continue
            # ----- check whether the same link has been added before -----
            info = (link.l_node._label, link.r_node._label, link._label, link._type)
            if info in link_info2idx_map:
                self.Links[link_info2idx_map[info]].times += link.times
            else:
                link_info2idx_map[info] = len(self.Links)
                self.Links.append(link)
        # ----- build Adjacent Matrix for the Theme SLN -----
        self.adj_matrix = self.BuildAdjMatrix()

    def __len__(self):
        return len(self.Nodes)

    # ---- insure that the nid of a node represents its index in the self.Nodes list ----
    def ReviseNid(self):
        revised = False
        for idx, node in enumerate(self.Nodes):
            if node.nid != idx:
                node.nid = idx
                revised = True
        if revised:
            self.adj_matrix = self.BuildAdjMatrix()
        return revised

    def BuildAdjMatrix(self):
        adj_matrix = {}
        added_dict = {}
        for link in self.Links:
            link_info = {'label': link._label, 'type': link._type, 'level': link.level, 'times': link.times}
            nid_key = (link.l_node.nid, link.r_node.nid)
            add_key = (nid_key, (link._label, link._type))
            if nid_key not in adj_matrix:
                added_dict[add_key] = 0
                adj_matrix[nid_key] = [link_info]
            else:
                if add_key in added_dict:
                    pre_link = adj_matrix[nid_key][added_dict[add_key]]
                    pre_link['level'] = min(pre_link['level'], link.level)
                    pre_link['times'] += link.times
                else:
                    added_dict[add_key] = len(adj_matrix[nid_key])
                    adj_matrix[nid_key].append(link_info)
        return adj_matrix

    def MergeSLN(self, new_SLN):
        # ----- Check the input object whether it is a Theme SLN -----
        if type(new_SLN).__name__ != "ThemeSLN":
            print("The input is not a theme SLN!")
            return
        # ----- map the node label to its index in self.Nodes -----
        node_label2idx_map = {}
        for idx, node in enumerate(self.Nodes):
            node_label2idx_map[node._label] = idx
        # ----- check nodes in new_SLN to add them into self.Nodes -----
        for node in new_SLN.Nodes:
            if node._label in node_label2idx_map:
                idx = node_label2idx_map[node._label]
                self.Nodes[idx].times += node.times
                self.Nodes[idx].level = min(node.level, self.Nodes[idx].level)
            else:
                node_label2idx_map[node._label] = len(self.Nodes)
                node.nid = node_label2idx_map[node._label]
                self.Nodes.append(node)
        # ----- check links in new_SLN to add them into self.Links -----
        link_info2idx_map = {}
        for idx, link in enumerate(self.Links):
            info = (link.l_node.nid, link.r_node.nid, link._label, link._type)
            link_info2idx_map[info] = idx
        for link in new_SLN.Links:
            info = (link.l_node.nid, link.r_node.nid, link._label, link._type)
            if info in link_info2idx_map:
                idx = link_info2idx_map[info]
                self.Links[idx].times += link.times
            else:
                link.l_node = self.Nodes[node_label2idx_map[link.l_node._label]]
                link.r_node = self.Nodes[node_label2idx_map[link.r_node._label]]
                link_info2idx_map[info] = len(self.Links)
                self.Links.append(link)
        # ----- Build the Adjacent Matrix for the merged theme SLN -----
        self.adj_matrix = self.BuildAdjMatrix()
        return

    def showNodes(self):
        print("================== Nodes =================")
        for node in self.Nodes:
            print("Node ID:", node.nid)
            print("Node string:", node._label)
            print("Node level:", node.level)
            print("Node times:", node.times)
            print("Merge Nodes:", ';'.join([merge_n._label for merge_n in node.merge_nodes]))
            print("-------------------------------")
        return

    def showLinks(self):
        print("================== Links =================")
        for link in self.Links:
            print(link.l_node._label + ":" + str(link.l_node.nid),
                  "--" + ':'.join([link._label, link._type, str(link.times)])
                  + "-->", link.r_node._label + ":" + str(link.r_node.nid))
            print("-------------------------------")
        return

    def showAdjMatrix(self):
        print("================== Adjacent Matrix =================")
        for i_idx in range(len(self.Nodes)):
            for j_idx in range(len(self.Nodes)):
                if (i_idx, j_idx) in self.adj_matrix:
                    print((i_idx, j_idx), self.adj_matrix[(i_idx, j_idx)])
                    print("-------------------------------")
        return


#######################################################################################
# ------------------------------- Calculate Similarity ------------------------------ #
#######################################################################################
def ProcessTxt2Words(stxt, _stem=True, _stopw=True):
    if type(stxt) is not str:
        return []
    wlist = nltk.word_tokenize(stxt.lower())
    if _stem:
        wlist = [porter_stemmer.stem(w) for w in wlist]
    if _stopw:
        wlist = [w for w in wlist if w not in RemoveWords]
    return wlist


# ----- Calculate the Jaccard similarity between two text segments -----
# _stem = True: whether to do stem reduction on each words.
# _stopw = True: remove stopwords and punctions from two texts.
def jcd_similarity(A_text, B_text, _stem=False, _stopw=True):
    A_wordset = set(ProcessTxt2Words(A_text, _stem, _stopw))
    B_wordset = set(ProcessTxt2Words(B_text, _stem, _stopw))
    s1 = A_wordset.intersection(B_wordset)
    s2 = A_wordset.union(B_wordset)
    if len(s2) == 0:
        return 0.0
    return float(len(s1)) / float(len(s2))


# ----- Calculate the 1gram BLEU similarity between two text segments -----
# _stem = True: whether to do stem reduction on each words.
# _stopw = True: remove stopwords and punctions from two texts.
# _n: the maximum ngram that we used to calculate BLEU
def bleu_similarity(ref_text, obj_text, _stem=False, _stopw=True, _ngram=1):
    ref_words = ProcessTxt2Words(ref_text, _stem, _stopw)
    obj_words = ProcessTxt2Words(obj_text, _stem, _stopw)
    chencherry = SmoothingFunction()
    bleu_n2vals = {}
    for n in range(1, _ngram+1):
        _val = sentence_bleu([ref_words], obj_words, tuple([1/n]*n), smoothing_function=chencherry.method1)
        bleu_n2vals['BLEU-'+str(n)] = float(_val)
    return bleu_n2vals


# ----- Calculate the Embedding similarity between two text segments -----
def emb_similarity(A_emb, B_emb):
    if A_emb is None or B_emb is None:
        return 0.0
    else:
        return max(float(cosine_similarity(A_emb, B_emb)), 0.0)


# ----- According to the type to call the function to calculate the similarity between a_label and b_label -----
def GetSimValue(a_label, b_label, simtype='emb', a_emb=None, b_emb=None):
    if simtype == 'jcd':
        return jcd_similarity(a_label, b_label)
    elif simtype == 'bleu':
        return (bleu_similarity(a_label, b_label)['BLEU-1'] + bleu_similarity(b_label, a_label)['BLEU-1']) / 2
    elif simtype == 'emb':
        return emb_similarity(a_emb, b_emb)
    elif simtype == 'mix':
        return max(jcd_similarity(a_label, b_label), emb_similarity(a_emb, b_emb),
                   (bleu_similarity(a_label, b_label)['BLEU-1'] + bleu_similarity(b_label, a_label)['BLEU-1']) / 2)
    else:
        return 0.0


#######################################################################################
# -------------------- Build Theme SLN & Operations on Theme SLN -------------------- #
#######################################################################################
def GetNodesLinks(PTree, Nodes, Links, _merge=False, level=0):
    # ---- If current tree node is a leaf node, stop iteration on this branch ----
    if type(PTree) is not Tree:
        return Nodes, Links, _merge
    # ------ Height = 2, may be a link ------
    if PTree.height() == 2:
        # -- If current node is a conjunction like 'and', 'or', activate _merge parameter --
        if PTree.label() == 'CC':
            return Nodes, Links, True
        # -- If Nodes contains no node, skip to process this link --
        if len(Nodes) == 0:
            return Nodes, Links, False
        # -- If current tree is a prep, verb, to or adverb not ends with 'ly', construct it as a link --
        if PTree.label()[:2] in ['IN', 'TO', 'MD', 'PR', 'VB'] or (
                (PTree.label() == 'RB' and not PTree[0].endswith('ly'))):
            temp_link = ThemeLink(PTree[0], PTree.label()[:2], level, None, None, 1)
        # -- for other tree label, do not need to parse --
        else:
            return Nodes, Links, _merge
        # -- if _merge is activate, add temp_link between the nodes connected by the last link --
        if len(Links) > 0 and _merge:
            temp_link.l_node = Links[-1].l_node
            temp_link.r_node = Links[-1].r_node
            _merge = False
        # -- check the near node to connect the link --
        else:
            for node in Nodes[::-1]:
                if node.level <= temp_link.level:
                    temp_link.l_node = node
                    break
        # -- if current link has left node to link --
        if temp_link.l_node is not None:
            # -- for merge_nodes in temp_link's left node, new link for the merge_node --
            for merge_node in temp_link.l_node.merge_nodes:
                new_link = copy.deepcopy(temp_link)
                new_link.l_node = merge_node
                Links.append(new_link)
            Links.append(temp_link)
        return Nodes, Links, _merge

    # ------ If the tree is labeled as 'NP' and contains no NP in its children, it is a node ------
    if PTree.label() == 'NP' and 'NP' not in [subtree.label() for subtree in PTree.subtrees() if subtree != PTree]:
        # -- get the label of the node --
        words_tags = []
        for child in PTree.subtrees(lambda t: t.height() == 2):
            if child.label() not in ['DT', '-LRB-', '-RRB-'] or child[0].lower() in ['no']:
                words_tags.append((child[0], child.label()))
        # -- if current NP tree contains nouns, build it as a theme node --
        if len(words_tags) > 0:
            temp_node = ThemeNode(len(Nodes), words_tags, level, 1)
            # -- if added before, pop it --
            idx = 0
            while idx < len(Nodes):
                if temp_node == Nodes[idx]:
                    Nodes[idx].times += temp_node.times
                    Nodes[idx].level = min(Nodes[idx].level, temp_node.level)
                    temp_node = Nodes.pop(idx)
                    break
                else:
                    idx += 1
            # -- check whether need to be merged with the last node --
            if _merge and len(Nodes) > 0:
                temp_node.merge_nodes.append(Nodes[-1])
                Nodes[-1].merge_nodes.append(temp_node)
                _merge = False
            Nodes.append(temp_node)
            # -- if Links contains links, process links that has no right node --
            if len(Links) > 0 and Links[-1].r_node is None and Links[-1].level - 1 <= temp_node.level:
                # -- merge links that contains no r_node, connect to the current node --
                last_link = ThemeLink([], Links[-1]._type, Links[-1].level, Links[-1].l_node, temp_node, 1)
                while len(Links) > 0 and Links[-1].level <= last_link.level and Links[-1].r_node is None and Links[
                    -1].l_node.level <= last_link.l_node.level:
                    last_link._label.append(Links[-1]._label)
                    last_link.times = max(last_link.times, Links[-1].times)
                    last_link.level = Links[-1].level
                    last_link.l_node = Links[-1].l_node
                    if Links[-1]._type == 'VB' or (Links[-1]._type == 'MD' and last_link._type != 'VB'):
                        last_link._type = Links[-1]._type
                    Links.pop(-1)
                if len(last_link._label) > 0:
                    last_link._label = ' '.join(last_link._label[::-1])
                    Links.append(last_link)
            # -- check links that have no r_node, connect to the current node --
            for link in Links:
                if link.r_node is None and link.level - 1 <= temp_node.level:
                    link.r_node = temp_node
                # -- check the merge nodes --
                for merge_n in temp_node.merge_nodes:
                    if link.r_node == merge_n and link.l_node != temp_node:
                        temp_link = ThemeLink(link._label, link._type, link.level, link.l_node, temp_node, 1)
                        Links.append(temp_link)
        return Nodes, Links, _merge
    # ------- For other type of Nodes, visit its children --------
    for child in PTree:
        Nodes, Links, _merge = GetNodesLinks(child, Nodes, Links, _merge, level + 1)
    return Nodes, Links, _merge


def BuildSLNforSents(Sents, SLNtype='sent', _tab=""):
    print(_tab + '\033[35m%s\033[0m' % 'Building the theme SLN for sentences ...')
    # ---- if the language cannot be processed or the input is not a sentence or a tree or a list -----
    if type(Sents) not in [str, Tree, list]:
        return ThemeSLN([], [], SLNtype)
    # ------ if Sents is a single string of sentence, build a theme SLN for it --------
    if type(Sents) is str:
        if not Sents.strip():
            return ThemeSLN([], [], SLNtype)
        try:
            ptree = GetSingleStanfordPTree(Sents)
            Nodes, Links, _merge = GetNodesLinks(ptree, [], [], _merge=False, level=0)
            return ThemeSLN(Nodes, Links, SLNtype)
        except:
            return ThemeSLN([], [], SLNtype)
    # ------ if Sents is a parser tree, build a theme SLN for it --------
    if type(Sents) is Tree:
        Nodes, Links, _merge = GetNodesLinks(Sents, [], [], _merge=False, level=0)
        return ThemeSLN(Nodes, Links, SLNtype)
    # ------ if Sents is a list of string, convert it into a list of Parser Trees ------
    PTrees, SentSLNs = [], []
    if BoolAND([type(sent) is str for sent in Sents]):
        PTrees = GetStanfordPTrees(Sents)
    else:
        for sent in Sents:
            if type(sent) is Tree:
                PTrees.append(sent)
            elif type(sent) is str:
                PTrees.append(GetSingleStanfordPTree(sent))
            else:
                PTrees.append(Tree('ROOT', []))
    for ptree in PTrees:
        Nodes, Links, _merge = GetNodesLinks(ptree, [], [], _merge=False, level=0)
        SentSLNs.append(ThemeSLN(Nodes, Links, SLNtype))
    return SentSLNs


def MergeSentsSLN(SentSLNs, SLNtype='source'):
    # ----- Check the type of the input -----
    if type(SentSLNs).__name__ not in ["ThemeSLN", "list"]:
        return ThemeSLN([], [], SLNtype)
    # ----- if the SentSLNs is a single SLN -----
    if isinstance(SentSLNs, ThemeSLN):
        return SentSLNs
    # ----- if the SentSLNs is a list, merge each SLN into merged_SLN -----
    merged_SLN = ThemeSLN([], [], SLNtype)
    for sent_sln in SentSLNs:
        if isinstance(sent_sln, ThemeSLN):
            merged_SLN.MergeSLN(sent_sln)
    return merged_SLN


# ---- FindSameNodes: find the most similar nodes of A_SLN in B_SLN ----
# Inputs:
#   1. A_SLN: the target SLN that contains the nodes that we want to find the most similar nodes
#   2. B_SLN: the object SLN from which we find the most similar nodes for each node in A_SLN
#   3. simtype: the type for the similarity, should be one in ['jcd', 'bleu', 'emb', 'mix']
#   4. nsim_thr: the threshold for the minimum similarity of the most similar node-pair.
#   5. A_Vecs: the embeddings for nodes and links within A_SLN, for "emb" and "mix" simtype, default as {}
#   6. B_Vecs: the embeddings for nodes and links within B_SLN, for "emb" and "mix" simtype, default as {}
def FindSameNodes(A_SLN, B_SLN, simtype='mix', nsim_thr=0.7, A_Vecs={}, B_Vecs={}):
    A2B_node_map = {}
    for an in A_SLN.Nodes:
        a_emb = A_Vecs.get((an._label, 'node'))
        max_bn, max_sim = None, -1
        for bn in B_SLN.Nodes:
            b_emb = B_Vecs.get((bn._label, 'node'))
            temp_sim = GetSimValue(an._label, bn._label, simtype, a_emb, b_emb)
            if temp_sim > max_sim:
                max_bn, max_sim = bn, temp_sim
        if max_sim > nsim_thr:
            A2B_node_map[an.nid] = (max_bn, max_sim)
    gc.collect()
    return A2B_node_map


# ---- ExtendSLN: extend A_SLN by finding nodes that are linguistically linked to A_SLN's nodes within B_SLN ----
# Inputs:
#   1. A_SLN: the target SLN that is needed to extend.
#   2. B_SLN: the source SLN from which we find nodes to extend A_SLN.
#   3. scale: the extend scale, must be a positive interger, default as 1
#   4. simtype: the type for find A_SLN's most similar nodes from B_SLN, should be one in ['jcd', 'bleu', 'emb', 'mix']
#   5. nsim_thr: the threshold for judging the most similar nodes
#   6. A_Vecs: the embeddings for nodes and links within A_SLN, for "emb" and "mix" simtype, default as {}
#   7. B_Vecs: the embeddings for nodes and links within B_SLN, for "emb" and "mix" simtype, default as {}
#   8. omlink_types: the type of links that should be omit when extending.
def ExtendSLN(A_SLN, B_SLN, scale=1, simtype='jcd', nsim_thr=0.9, A_Vecs={}, B_Vecs={}, omlink_types={'LEAD'}, _tab=""):
    # ---- Check the type of the input ----
    if not isinstance(A_SLN, ThemeSLN) or not isinstance(B_SLN, ThemeSLN):
        print(_tab + '\033[31m%s\033[0m' % "Error! The input is not a theme SLN!")
        return A_SLN
    # ---- check extend scale of nodes ----
    if type(scale) is not int or scale <= 0:
        print(_tab + '\033[31m%s\033[0m' % "Error! The input of extended iter_times should be a positive integer")
        return A_SLN
    # ---- revise nodes in A_SLN ----
    B_SLN.ReviseNid()
    A_SLN.ReviseNid()
    for an in A_SLN.Nodes:
        an.level = 0
    # ---- revise links in A_SLN ----
    A_link2idx_map = {}
    for idx, al in enumerate(A_SLN.Links):
        al.level = 0
        A_link2idx_map[(al.l_node._label, al.r_node._label, al._label, al._type)] = idx
    # ---- Get the existing Node ID mapping dict ----
    A2B_node_map = FindSameNodes(A_SLN, B_SLN, simtype, nsim_thr, A_Vecs, B_Vecs)
    added_b2a_nids = {bn.nid: anid for anid, (bn, sim) in A2B_node_map.items()}
    # ---- Extend A_SLN by finding nodes that are linguistically linked to its most similar nodes within B_SLN ----
    for _iter in range(1, scale + 1):
        extend_flag, exist_b_nids = False, set(added_b2a_nids.keys())
        for pre_nid in exist_b_nids:
            for bn in B_SLN.Nodes:
                # -- skip bn that has been added into A_SLN.Nodes --
                if bn.nid in added_b2a_nids:
                    continue
                # -- add bn into A_SLN.Nodes if it has links connected to node that is already added into A_SLN --
                in_links = B_SLN.adj_matrix.get((bn.nid, pre_nid), [])
                in_flag = BoolOR(list(map(lambda x: x['type'] not in omlink_types, in_links)))
                out_links = B_SLN.adj_matrix.get((pre_nid, bn.nid), [])
                out_flag = BoolOR(list(map(lambda x: x['type'] not in omlink_types, out_links)))
                if in_flag or out_flag:
                    extend_flag = True
                    new_an = copy.deepcopy(bn)
                    new_an.level = _iter
                    new_an.nid = len(A_SLN.Nodes)
                    added_b2a_nids[bn.nid] = new_an.nid
                    A_SLN.Nodes.append(new_an)
        if not extend_flag:
            break
    # ---- added extended links into A_SLN ----
    for bl in B_SLN.Links:
        if bl.l_node.nid not in added_b2a_nids or bl.r_node.nid not in added_b2a_nids:
            continue
        linfo = (bl.l_node._label, bl.r_node._label, bl._label, bl._type)
        if linfo in A_link2idx_map:
            old_al = A_SLN.Links[A_link2idx_map[linfo]]
            old_al.times = max(old_al.times, bl.times)
        else:
            new_al = copy.deepcopy(bl)
            new_al.l_node = A_SLN.Nodes[added_b2a_nids[bl.l_node.nid]]
            new_al.r_node = A_SLN.Nodes[added_b2a_nids[bl.r_node.nid]]
            new_al.level = max(new_al.l_node.level, new_al.r_node.level)
            A_SLN.Links.append(new_al)
    # ------ Get the Adjacent Matrix for the extended SLN ------
    A_SLN.adj_matrix = A_SLN.BuildAdjMatrix()
    return A_SLN


def WriteAdjMatrix2Excel(theme_sln, excel_fp):
    if not isinstance(theme_sln, ThemeSLN):
        print('\t\033[33m%s\033[0m' % 'Error! the input is not a Theme SLN ...')
    workbook = xlwt.Workbook(encoding='utf-8')
    worksheet = workbook.add_sheet("Adjacent_Matrix")
    for nidx in range(len(theme_sln.Nodes)):
        worksheet.write(nidx + 1, 0, theme_sln.Nodes[nidx]._label)
        worksheet.write(nidx + 1, 1, nidx)
        worksheet.write(0, nidx + 2, nidx)
    for row_idx in range(len(theme_sln.Nodes)):
        for col_idx in range(len(theme_sln.Nodes)):
            if (row_idx, col_idx) in theme_sln.adj_matrix:
                link_string = ""
                for link_info_dict in theme_sln.adj_matrix[(row_idx, col_idx)]:
                    if link_info_dict['type'] == 'LEAD':
                        link_string += "{:.3f}".format(link_info_dict['times']) + '; '
                    else:
                        link_string += link_info_dict['label'] + '; '
                worksheet.write(row_idx + 1, col_idx + 2, link_string.rstrip("; "))
    workbook.save(excel_fp)


# ---- Draw ThemeSLN in Graph -----
def DrawSLN(thmSLN, nlabel=True, llabel=True, nclr='#87CEEB', eclr="#DAA520", etagclr="#7E5109"):
    G = nx.DiGraph()
    # ----- linguistic links -------
    for node in thmSLN.Nodes:
        if nlabel:
            G.add_node(node._label)
        else:
            G.add_node(node.nid)
    for link in thmSLN.Links:
        if nlabel:
            if llabel:
                G.add_edge(link.l_node._label, link.r_node._label, tag=link._type + ": " + link._label)
            else:
                G.add_edge(link.l_node._label, link.r_node._label)
        else:
            if llabel:
                G.add_edge(link.l_node.nid, link.r_node.nid, tag=link._type + ": " + link._label)
            else:
                G.add_edge(link.l_node.nid, link.r_node.nid)

    pos = nx.spring_layout(G)
    etags_dict = nx.get_edge_attributes(G, 'tag')
    nx.draw_networkx(G, pos, with_labels=True, node_color=nclr, edge_color=eclr)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=etags_dict, font_color=etagclr, font_size=8)
    plt.show()
    return


#######################################################################################
# ---------------------- Add lead links between theme nodes ------------------------- #
#######################################################################################
# -- lead_scope == 2 : the leading-ship exists within the same sentence and adjacent two sentences ---
def GetLeadInfo(sentSLNs, lead_scope=2):
    lead_info_list = []
    # ---- the lead information within the same sentence ----
    node_lead_map = {}
    for sln in sentSLNs:
        for preidx, pre_n in enumerate(sln.Nodes):
            for cur_n in sln.Nodes[preidx + 1:]:
                node_lead_map[(pre_n._label, cur_n._label)] = cur_n.times
    lead_info_list.append(node_lead_map.copy())
    # ---- the lead information in adjacent sentences within the lead_scope ----
    for gap in range(1, lead_scope):
        # -- raw_node_lead_maps add sent-id to remove repeat matchings brought by situations like "A,B; A,B" --
        # -- where 'B' in 2nd sentence will be matched twice by the same-sent match and adjacent-sent match --
        raw_node_lead_maps = {}
        for sid in range(gap, len(sentSLNs)):
            for pre_n in sentSLNs[sid - gap].Nodes:
                for cur_n in sentSLNs[sid].Nodes:
                    lead_key = (pre_n._label, (cur_n._label, sid))
                    if lead_key not in raw_node_lead_maps:
                        raw_node_lead_maps[lead_key] = cur_n.times
        # ---- delete sent-id information from the node_lead_maps dict ----
        node_lead_map = {}
        for lead_key, lead_times in raw_node_lead_maps.items():
            if (lead_key[0], lead_key[1][0]) in node_lead_map:
                node_lead_map[(lead_key[0], lead_key[1][0])] += lead_times
            else:
                node_lead_map[(lead_key[0], lead_key[1][0])] = lead_times
        lead_info_list.append(node_lead_map.copy())
    # ---- show lead_info_list ----
    # for sent_scape, node_ld_map in enumerate(lead_info_list):
    #     print("================= lead times within %d sents ==================" % sent_scape)
    #     for nlabel_tuple in node_ld_map:
    #         print(nlabel_tuple, "-->", node_ld_map[nlabel_tuple])
    return lead_info_list


def GetLeadPKForSrcFile(srcfp, pkdir, lead_scope=2, _tab=""):
    # ---- If the leading information has been built before, check if the information corresponds lead_scope ----
    ldinfo_pkfp = os.path.join(pkdir, os.path.basename(srcfp) + '.LeadInfo.pk')
    if os.path.isfile(ldinfo_pkfp):
        lead_info_list = Loadpickle(ldinfo_pkfp)
        # -- if corresponds, just load and return it --
        if len(lead_info_list) == lead_scope:
            return lead_info_list
        # -- else, delete the previous leading information --
        else:
            os.remove(ldinfo_pkfp)
    # ---- Load source SLNs ----
    srcSLNs = GetFileCacheDatas(srcfp, dtype='srcSLNs', pkfile_dir=pkdir, _tab=_tab)
    # ---- Get LeadInfo in srcSLNs ----
    lead_info_list = GetLeadInfo(srcSLNs, lead_scope)
    # ---- Dump Pickle File ----
    Dumppickle(ldinfo_pkfp, lead_info_list)
    return lead_info_list


def Check_ld_ratio(ld_ratios):
    # -- check the type of ld_ratios --
    err_flag = not type(ld_ratios) in [list, tuple]
    # -- check each element in the ld_ratios --
    if not err_flag:
        err_flag = not BoolAND(list(map(lambda x: type(x) in [int, float] and x >= 0.0, ld_ratios)))
    # -- check whether the sum of ld_ratios is not zero --
    if not err_flag:
        err_flag = (sum(ld_ratios) == 0)
    # -- scale the lead ratios --
    if not err_flag:
        ld_ratios = tuple(map(lambda x: x / sum(ld_ratios), ld_ratios))
    return err_flag, ld_ratios


def GetLeadWeight(na, nb, lead_info_list, nfreq_thr=0, ld_ratios=(0.6, 0.4)):
    ld_weight = 0.0
    err_flag, ld_ratios = Check_ld_ratio(ld_ratios)
    if not err_flag and 0 <= nfreq_thr < nb.times:
        for gap, rt in enumerate(ld_ratios):
            ld_weight += lead_info_list[gap].get((na._label, nb._label), 0) * rt
        ld_weight = ld_weight / nb.times
    return ld_weight


def AddLeadLinks(leadSLN, lead_info_list, node_map=None, nfreq_thr=0, ld_ratios=(0.6, 0.4), _tab=""):
    # ---- check errors caused by ld_ratio ----
    err_flag, ld_ratios = Check_ld_ratio(ld_ratios)
    if err_flag:
        err_msg = "Errors! The ld_ratios is a tuple/list of positive values to weight lead within different sent_scope!"
        print(_tab + '\033[31m%s\033[0m' % err_msg)
        return leadSLN
    # ---- initiate node_map (map leadSLN's nodes to lead_info_list's nodes) when it is not given ----
    if node_map is None:
        node_map = {node.nid: (node, 1.0) for node in leadSLN.Nodes}
    # ---- Add lead links into leadSLN ----
    for n1 in leadSLN.Nodes:
        for n2 in leadSLN.Nodes:
            if n1 == n2 or n1.nid not in node_map or n2.nid not in node_map:
                continue
            (na, nasim), (nb, nbsim) = node_map[n1.nid], node_map[n2.nid]
            ld_weight = GetLeadWeight(na, nb, lead_info_list, nfreq_thr, ld_ratios) * min(nasim, nbsim)
            if ld_weight > 0:
                leadSLN.Links.append(ThemeLink("LEAD-TO", 'LEAD', 0, n1, n2, ld_weight))
    leadSLN.adj_matrix = leadSLN.BuildAdjMatrix()
    return leadSLN


#######################################################################################
# --------------- Embedding Node Link and sentence into vectors --------------------- #
#######################################################################################
def remove_first_principal_component(X):
    svd = TruncatedSVD(n_components=1, n_iter=7, random_state=0)
    svd.fit(X)
    pc = svd.components_
    XX = X - X.dot(pc.transpose()) * pc
    return XX


def GetLabelGenreTuples(theme_sln, omlink_types=('LEAD'), _tab=""):
    label_genre_tuples = []
    if type(theme_sln).__name__ != "ThemeSLN":
        print(_tab + '\033[31m%s\033[0m' % 'Error! The input is not a ThemeSLN, cannot get its label_genre_tuples')
        return label_genre_tuples
    for node in theme_sln.Nodes:
        label_genre_tuples.append((node._label, 'node'))
    for link in theme_sln.Links:
        if link._type in omlink_types:
            continue
        label_genre_tuples.append((link._label, 'link'))
    return label_genre_tuples


# ----- Embedding Nodes and Links text into vectors -----
def EmbedNodesLinks(label_genre_tuples, embopt='avg', stopword=0, _tab=""):
    print(_tab + '\033[33m%s\033[0m' % 'Getting the embeddings for (text, type) tuples, type in [node, link]...')
    # -- if sents_list is an empty list or is an empty string --
    if not label_genre_tuples:
        return {}
    # -- The words needed to be removed from the text --
    rmwords = set()
    if stopword:
        rmwords = RemoveWords
    # -- if sents_list is a (text, type) tuple or is a string, convert it into a list --
    if type(label_genre_tuples) is tuple:
        label_genre_tuples = [label_genre_tuples]
    elif type(label_genre_tuples) is str:
        label_genre_tuples = [(label_genre_tuples, "unknown")]
    # ---- Getting the embedding vector for each each sentence ----
    label_vectors = {}
    for cur_tuple in label_genre_tuples:
        # print("-----------------------------")
        # print(cur_tuple)
        # -- process each sentence into a words list --
        wordslist = map(lambda x: x.lower(), nltk.word_tokenize(cur_tuple[0]))
        wordslist = [w for w in wordslist if w not in rmwords and w in word_vector]
        # -- If the no words left, append None for this sentence --
        if not wordslist:
            # print("no words remain ...")
            label_vectors[cur_tuple] = None
            continue
        # -- Get all different words and their frequency --
        wfreqdict = Counter(wordslist)
        wordset = wfreqdict.keys()
        # -- for 'avg' embedding type, the weights for words in the wordset are set to be None --
        weights = None
        # -- for 'avg-tfidf' embedding type, change the weights according to wiki_wordTFIDF information --
        if embopt == 'avg_tfidf':
            NUM_DOCS = wiki_wordTFIDF['NUM_DOCS']
            weights = [wfreqdict[w] * math.log(NUM_DOCS / (wiki_wordTFIDF.get(w, 0) + 1)) for w in wordset]
        # -- for 'sif' embedding type, change the weights according to wiki_wordfreq information --
        elif embopt == 'sif':
            a = 0.001  # -- 'a' is the parameter for SIF model --
            total_freq = sum(wiki_wordfreq.values())
            weights = [a / (a + wiki_wordfreq.get(w, 0) / total_freq) for w in wordset]
        # -- Adding the embedding vector for the sentence --
        label_vectors[cur_tuple] = np.average([word_vector[w] for w in wordset], axis=0, weights=weights).reshape(1, -1)
        # print("weights:", weights)
        # print(label_vectors[cur_tuple])
    # ---- If the embopt is "sif", the embedding vectors for each node need to minus the first principle vector ----
    if embopt == 'sif':
        # -- Remove None from the 'embeddings' list, and store the alignment of index --
        remained_vectors = []
        remained_tuples = []
        for label_tuple, vec in label_vectors.items():
            if vec is not None:
                remained_vectors.append(vec)
                remained_tuples.append(label_tuple)
        remained_vectors = remove_first_principal_component(np.array(remained_vectors))
        for idx, label_tuple in enumerate(remained_tuples):
            label_vectors[label_tuple] = remained_vectors[idx].reshape(1, -1)
    return label_vectors


def EmbedSents2Vectors(sents_list, embopt='avg', stopword=False, _tab=""):
    print(_tab + '\033[33m%s\033[0m' % 'Getting the embeddings list for the sentence list ...')
    # -- if sents_list is an empty list or is an empty string --
    if not sents_list:
        return []
    # -- if sents_list is a single sentence, convert the string into a list --
    if type(sents_list) is str:
        sents_list = [sents_list]
    # -- The words needed to be removed from the text --
    rmwords = set()
    if stopword:
        rmwords = RemoveWords
    # ---- Getting the embedding vector for each each sentence ----
    embeddings = []
    for sent in sents_list:
        # -- process each sentence into a words list --
        wordslist = map(lambda x: x.lower(), nltk.word_tokenize(sent))
        wordslist = [w for w in wordslist if w not in rmwords and w in word_vector]
        # -- If the no words left, append None for this sentence --
        if not wordslist:
            embeddings.append(None)
            continue
        # -- Get all different words and their frequency --
        wfreqdict = Counter(wordslist)
        wordset = wfreqdict.keys()
        # -- for 'avg' embedding type, the weights for words in the wordset are set to be None --
        weights = None
        # -- for 'avg-tfidf' embedding type, change the weights according to wiki_wordTFIDF information --
        if embopt == 'avg_tfidf':
            NUM_DOCS = wiki_wordTFIDF['NUM_DOCS']
            weights = [wfreqdict[w] * math.log(NUM_DOCS / (wiki_wordTFIDF.get(w, 0) + 1)) for w in wordset]
        # -- for 'sif' embedding type, change the weights according to wiki_wordfreq information --
        elif embopt == 'sif':
            a = 0.001  # -- 'a' is the parameter for SIF model --
            total_freq = sum(wiki_wordfreq.values())
            weights = [a / (a + wiki_wordfreq.get(w, 0) / total_freq) for w in wordset]
        # -- Adding0 the embedding vector for the sentence --
        embeddings.append(np.average([word_vector[w] for w in wordset], axis=0, weights=weights).reshape(1, -1))
    # ---- If the embopt is "sif", the embedding vectors for each node need to minus the first principle vector ----
    if embopt == 'sif':
        # -- Remove None from the 'embeddings' list, and store the alignment of index --
        remained_embeddings = []
        remained_sid = []
        for sid, emb in enumerate(embeddings):
            if emb is not None:
                remained_embeddings.append(emb)
                remained_sid.append(sid)
        remained_embeddings = remove_first_principal_component(np.array(remained_embeddings))
        for idx, sid in enumerate(remained_sid):
            embeddings[sid] = remained_embeddings[idx].reshape(1, -1)

    return embeddings


#######################################################################################
# --------------- Calculate the similarity between two ThemeSLN --------------------- #
#######################################################################################
def _norm(vec):
    if np.min(vec) < 0.0:
        vec = vec - np.min(vec)
    if np.max(vec) > 1.0:
        return vec / np.max(vec)
    else:
        return np.array(vec)


# ------- GetNodeSim: get the similarity matrix between nodes of two theme SLNs ------
# Take both the label-similarity of nodes and the topology-similarity of nodes brought by links
# Input:
# 1. A_SLN, B_SLN: the two theme SLN that is required to calculate the similarity.
# 2. simtype: the way to calculate the similarity between labels of nodes and links.
#       (a) jcd: Jaccard similarity;
#       (b) emb: Embedding-based similarity;
#       (c) bleu: BLEU-based similarity;
#       (4) mix: the maximum of the first three type.
# 3. A_EMBs, B_EMBs: The embedding vectors for the nodes and links in A_SLN and B_SLN.
# 4. take_freq: whether take the frequency into calculating the label-similarity of nodes and links.
# 5. max_iter: the maximum of iteration times for calculating the topology-similarity, default as 30 (usually 15~20)
# 6. min_update: the minimum update in each iteration, default as 10**(-6), stop iteration if the update < min_update.
# 7. tmlink_types: types of links that we use their times as link-sim-transW;
# 8. eqlink_types: types of links that can be viewed as equal, and do not need to compare their labels.
# 9. omlink_types: types of links that should be omit.
# Output:
#    A matrix with size len(A_SLN)*len(B_SLN), row is the nodes of A_SLN, column is the nodes of B_SLN.
def GetNodeSim(A_SLN, B_SLN, simtype='mix', A_EMBs={}, B_EMBs={}, take_freq=False, max_iter=30, min_update=10 ** (-6),
               tmlink_types=(), eqlink_types=('IN', 'TO', 'MD', 'RB'), omlink_types=('LEAD'), _tab=""):
    if not isinstance(A_SLN, ThemeSLN) or not isinstance(B_SLN, ThemeSLN):
        print(_tab + '\033[31m%s\033[0m' % 'Error! The type of the inputs is not ThemeSLN!')
        return None
    elif len(A_SLN) == 0 or len(B_SLN) == 0:
        print(_tab + '\033[31m%s\033[0m' % 'Error! There is no Nodes in the one of the two ThemeSLN!')
        return None

    # ====== Get the label-similarity between Nodes ======
    npair_labsim_vec = np.zeros(len(A_SLN) * len(B_SLN))
    npair_idxs = {}
    for an in A_SLN.Nodes:
        for bn in B_SLN.Nodes:
            npair_idxs[(an._label, bn._label)] = len(npair_idxs)
            labsim = GetSimValue(an._label, bn._label, simtype, A_EMBs.get((an._label, 'node')),
                                 B_EMBs.get((bn._label, 'node')))
            if labsim > 0:
                labsim = labsim * (an.times + bn.times) / 2.0 if take_freq else labsim
                npair_labsim_vec[npair_idxs[(an._label, bn._label)]] = labsim
    npair_labsim_vec = _norm(npair_labsim_vec)

    # ====== Get the similarity-value/similarity-label between links ======
    npair_num = len(npair_idxs)
    link_simM = [[Counter() for i in range(npair_num)] for j in range(npair_num)]
    # ---- visit all link-pairs like (al, bl), where al from A_SLN and bl from B_SLN to calculate their link-sim ----
    for al in A_SLN.Links:
        if al._type in omlink_types:
            continue
        for bl in B_SLN.Links:
            if bl._type in omlink_types:
                continue
            row_idx = npair_idxs.get((al.l_node._label, bl.l_node._label))
            col_idx = npair_idxs.get((al.r_node._label, bl.r_node._label))
            # ---- If there exists errors in the node linked by a_link or b_link, skip this pair of links ----
            if row_idx is None or col_idx is None:
                print(_tab + '\033[31m%s\033[0m' % 'Error! The Nodes linked by this pair of links are not correct!')
                continue
            # ---- Compare this pair of links, and get their similarity ----
            # -- if one of the link belongs to tmlink_types, us its times as the linksim --
            if al._type in tmlink_types and bl._type in tmlink_types:
                linksim = (al.times + bl.times) / 2.0
            elif al._type in tmlink_types:
                linksim = al.times
            elif bl._type in tmlink_types:
                linksim = bl.times
            # -- if both a_link and b_link belong to types in eqlink_types, use "eq-type" as the linksim --
            elif al._type in eqlink_types and bl._type in eqlink_types:
                linksim = 'eq-type'
            # -- if a_link or b_link belongs to link-type that should compare labels, calculate the label-similarity --
            else:
                linksim = GetSimValue(al._label, bl._label, simtype, A_EMBs.get((al._label, 'link')),
                                      B_EMBs.get((bl._label, 'link')))
                linksim = linksim * (al.times + bl.times) / 2.0 if take_freq else linksim
            # -- store current link-pair similarity into link_sim_Matrix --
            if isinstance(linksim, str) or linksim > 0:
                link_simM[row_idx][col_idx].update({linksim})
    # # ---- write link-sim-Matrix into excel file ----
    # workbook = xlwt.Workbook(encoding='utf-8')
    # worksheet = workbook.add_sheet("Org-linksim-M")
    # for npair in npair_idxs:
    #     row_idx = npair_idxs[npair]
    #     worksheet.write(0, row_idx + 1, ','.join(npair))
    #     worksheet.write(row_idx + 1, 0, ','.join(npair))
    #     for idx in range(npair_num):
    #         if link_simM[row_idx][idx]:
    #             worksheet.write(row_idx + 1, idx + 1, str(dict(link_simM[row_idx][idx])))

    # ====== Build the node-pair similarity transfer matrix ======
    # ---- Add reverse link to the link_sim_matrix to make it a symmetric matrix ----
    for row_idx in range(npair_num):
        for col_idx in range(row_idx + 1, npair_num):
            # -- skip empty Counter in link_simM --
            if not link_simM[row_idx][col_idx] and not link_simM[col_idx][row_idx]:
                continue
            # -- make link-sim-Counters at (row_idx, col_idx) and (col_idx, row_idx) symmetry--
            if not link_simM[row_idx][col_idx]:
                link_simM[row_idx][col_idx] = link_simM[col_idx][row_idx]
            elif not link_simM[col_idx][row_idx]:
                link_simM[col_idx][row_idx] = link_simM[row_idx][col_idx]
            else:
                r2c_count = link_simM[row_idx][col_idx]
                c2r_count = link_simM[col_idx][row_idx]
                common_count = Counter()
                for key in set(r2c_count.keys()).union(set(c2r_count.keys())):
                    common_count[key] = max(r2c_count[key], c2r_count[key])
                link_simM[row_idx][col_idx] = common_count
                link_simM[col_idx][row_idx] = common_count
    # # -- write symmetry linksim Matirx --
    # worksheet = workbook.add_sheet("Sym-linksim-M")
    # for npair in npair_idxs:
    #     row_idx = npair_idxs[npair]
    #     worksheet.write(0, row_idx + 1, ','.join(npair))
    #     worksheet.write(row_idx + 1, 0, ','.join(npair))
    #     for idx in range(npair_num):
    #         if link_simM[row_idx][idx]:
    #             worksheet.write(row_idx + 1, idx + 1, str(dict(link_simM[row_idx][idx])))
    # ---- count label-similarity and equal-similarity in link_simM ----
    ridx2sim_dict = {}
    for row_idx in range(npair_num):
        labsim_idxs, eqsim_idxs, total_labsim = set(), set(), 0.0
        for col_idx in range(npair_num):
            for linksim, times in link_simM[row_idx][col_idx].items():
                if linksim == 'eq-type':
                    eqsim_idxs.add(col_idx)
                else:
                    labsim_idxs.add(col_idx)
                    total_labsim += linksim * times
        ridx2sim_dict[row_idx] = (labsim_idxs, eqsim_idxs, total_labsim)
    # ---- Build the similarity transfer matrix ----
    npair_sim_transM = np.zeros((npair_num, npair_num))
    for row_idx in range(npair_num):
        (labsim_idxs, eqsim_idxs, total_labsim) = ridx2sim_dict[row_idx]
        # -- set self-loop links for isolated node-pairs --
        if not labsim_idxs and not eqsim_idxs:
            npair_sim_transM[row_idx][row_idx] = 1.0
            continue
        # -- process the only labsim of links for each node pair--
        elif not eqsim_idxs:
            # - add self-loop for the sum labsim is not reach 1.0 -
            if total_labsim < 1.0:
                npair_sim_transM[row_idx][row_idx] = 1.0 - total_labsim
                total_labsim = 1.0
            # - normalize link lab-sim between node pairs -
            for idx in labsim_idxs:
                temp = sum([labsim * times for labsim, times in link_simM[row_idx][idx].items()])
                npair_sim_transM[row_idx][idx] = temp / total_labsim
        # -- process node-pair that both has eqsim link and labsim link--
        else:
            labnum, eqnum = len(labsim_idxs), len(eqsim_idxs)
            # -- get bias for labsim transform weight ----
            labsim_bias = 1.0
            if total_labsim >= 2 * labnum / (2 * labnum + eqnum) > 0:
                labsim_bias = (2 * labnum / (2 * labnum + eqnum)) / total_labsim
            # -- calculate the transform weight for each pair of node-pairs --
            for idx in labsim_idxs:
                temp = sum([labsim * times for labsim, times in link_simM[row_idx][idx].items() if type(labsim) != str])
                npair_sim_transM[row_idx][idx] = temp * labsim_bias
            # -- get the value assigned for each equal-type link-similairty --
            per_equalsim = (1 - sum(npair_sim_transM[row_idx])) / sum(
                [link_simM[row_idx][idx]['eq-type'] for idx in eqsim_idxs])
            for idx in eqsim_idxs:
                npair_sim_transM[row_idx][idx] += link_simM[row_idx][idx]['eq-type'] * per_equalsim
    # # -- write trans Matirx --
    # worksheet = workbook.add_sheet("transM")
    # worksheet.write(0,  npair_num + 1, "ROW-SUM")
    # for npair in npair_idxs:
    #     row_idx = npair_idxs[npair]
    #     worksheet.write(0, row_idx + 1, ','.join(npair))
    #     worksheet.write(row_idx + 1, 0, ','.join(npair))
    #     for idx in range(npair_num):
    #         worksheet.write(row_idx + 1, idx + 1, round(npair_sim_transM[row_idx][idx], 3))
    #     worksheet.write(row_idx + 1, npair_num + 1, round(sum(npair_sim_transM[row_idx]), 2))
    # workbook.save(os.path.join(os.getcwd(), "check_transM.xls"))

    # ====== Iteration for calculating the final similarity between node-pairs ======
    npair_simvec = npair_labsim_vec.copy()
    for i in range(max_iter):
        new_npair_simvec = _norm(npair_labsim_vec * 0.5 + np.matmul(npair_sim_transM, npair_simvec) * 0.5)
        # -- counts how many node-pairs' similarity has been updated, break the iteration if no update -----
        changed_npairs = np.sum(np.abs(new_npair_simvec - npair_simvec) > min_update)
        # print("====================== %d Iteration =======================" % (i + 1))
        # print(changed_npairs, "node-pairs' similarity are updated")
        if changed_npairs == 0:
            break
        # -- update the node-pair similarity vector --
        npair_simvec = new_npair_simvec

    # ====== Generate final node-sim matrix ======
    node_sim_matrix = np.zeros((len(A_SLN.Nodes), len(B_SLN.Nodes)))
    A_lab2idx_dict = {node._label: idx for idx, node in enumerate(A_SLN.Nodes)}
    B_lab2idx_dict = {node._label: idx for idx, node in enumerate(B_SLN.Nodes)}
    for (a_lab, b_lab), idx in npair_idxs.items():
        a_idx, b_idx = A_lab2idx_dict[a_lab], B_lab2idx_dict[b_lab]
        node_sim_matrix[a_idx][b_idx] = npair_simvec[idx]
    gc.collect()
    return node_sim_matrix, A_lab2idx_dict, B_lab2idx_dict


def WriteNsimM2Table(nsimM, A_lab2idx_dict, B_lab2idx_dict, table_fp):
    workbook = xlwt.Workbook(encoding='utf-8')
    worksheet = workbook.add_sheet("objRow-sumCol")
    for a_lab, a_idx in A_lab2idx_dict.items():
        worksheet.write(a_idx + 1, 0, a_lab)
    for b_lab, b_idx in B_lab2idx_dict.items():
        worksheet.write(0, b_idx + 1, b_lab)
    for a_idx in A_lab2idx_dict.values():
        for b_idx in B_lab2idx_dict.values():
            worksheet.write(a_idx + 1, b_idx + 1, round(nsimM[a_idx][b_idx], 3))
    workbook.save(table_fp)


# ------- greedy_match: calculate the similarity based on a similarity matrix ------
# Input:
# 1. sim_matrix: the similarity matrix that store the node similarity between two SLN.
# 2. base_axis:
#    = 0: the node represented by each column is required to find a most similar row node to match it.
#    = 1: the node represented by each row is required to find a most similar column node to match it.
def greedy_match(sim_matrix, base_axis=0, _tab=""):
    if not isinstance(sim_matrix, np.ndarray) or len(sim_matrix.shape) != 2 or len(sim_matrix) == 0:
        print(_tab + '\033[31m%s\033[0m' % 'Error! The type of the input matrix is not correct!')
        return 0.0
    matched_scores = tuple(sim_matrix.max(axis=base_axis))
    matched_base_nidxs = tuple(sim_matrix.argmax(axis=base_axis))
    return {nidx: (matched_scores[nidx], matched_base_nidxs[nidx]) for nidx in range(sim_matrix.shape[1 - base_axis])}


def _pen(x, delta=1.0):
    return (np.e) ** (-(x ** 2) / (2 * delta ** 2))


# ------- greedy_match_pen: Greedy Matching with penalty on repeated matching ------
# Input:
# 1. sim_matrix: the similarity matrix that store the node similarity between two SLN.
# 2. base_axis:
#    = 0: the node represented by each column is required to find a most similar row node to match it.
#    = 1: the node represented by each row is required to find a most similar column node to match it.
# 3. delta: the parameter for the penalty on the repeated matching, should be the avg_nfreq of the base-side SLN
# 4. upsim: the maximum similarity in sim_matrix, used to make sure matched node-pairs do not be matched again.
def greedy_match_pen(sim_matrix, base_axis=0, delta=1.0, upsim=1.0, _tab=""):
    if not isinstance(sim_matrix, np.ndarray) or len(sim_matrix.shape) != 2 or len(sim_matrix) == 0:
        print(_tab + '\033[31m%s\033[0m' % 'Error! The type of the input matrix is not correct!')
        return {}
    run_matrix, nodenum = sim_matrix.copy(), sim_matrix.shape[1 - base_axis]
    nidx2match_dict = {}
    base_nidx2times_dict = {nidx: 0 for nidx in range(sim_matrix.shape[base_axis])}
    while len(nidx2match_dict) < nodenum:
        match_scores = run_matrix.max(axis=base_axis)
        match_base_nidxs = run_matrix.argmax(axis=base_axis)
        mt_nidx = match_scores.argmax()
        # ---- add current node into matched nodes if current node has been matched ----
        if mt_nidx not in nidx2match_dict:
            mt_score, base_nidx = match_scores[mt_nidx], match_base_nidxs[mt_nidx]
            # -- if current match similarity less than 0, means that no nodes can be matched, break --
            if mt_score < 0.0:
                break
            nidx2match_dict[mt_nidx] = (mt_score, base_nidx)
            # -- punish other nodes' similarity to current matched base node --
            base_nidx2times_dict[base_nidx] += 1
            temp_pen_sims = sim_matrix.take(base_nidx, axis=base_axis) * _pen(base_nidx2times_dict[base_nidx], delta)
            for nidx in range(nodenum):
                if base_axis == 0:
                    run_matrix[base_nidx, nidx] = min(run_matrix[base_nidx, nidx], temp_pen_sims[nidx])
                else:
                    run_matrix[nidx, base_nidx] = min(run_matrix[nidx, base_nidx], temp_pen_sims[nidx])
        # ---- delete current node's similarity to all other base-side nodes ----
        if base_axis == 0:
            run_matrix[:, mt_nidx] -= upsim
        else:
            run_matrix[mt_nidx, :] -= upsim
    for nidx in range(nodenum):
        if nidx not in nidx2match_dict:
            nidx2match_dict[nidx] = (0.0, None)

    return nidx2match_dict


# ---- match_scores: merge similarity of all node-pairs within nid2match_dict into one score ----
# Inputs:
#   1. nidx2match_dict: the dict stores the match information of node-pairs got by greedy_match(_pen).
#   2. _merge: the way to merge all node-pairs' similarity, should be one in ['avg', 'mid', 'pct'], default as 'avg'
#   3. mt_thr: the threshold for similarity in 'pct' (percentage of node-pairs whose similarity >= mt_thr)
def match_scores(nidx2match_dict, _opt='avg'):
    if not nidx2match_dict:
        return 0.0
    if _opt == 'avg':
        return np.average([mt_score for (mt_score, base_nidx) in nidx2match_dict.values()])
    if _opt == 'mid':
        return np.median([mt_score for (mt_score, base_nidx) in nidx2match_dict.values()])
    if _opt == 'max':
        return np.max([mt_score for (mt_score, base_nidx) in nidx2match_dict.values()])
    if _opt == 'min':
        return np.min([mt_score for (mt_score, base_nidx) in nidx2match_dict.values()])
    try:
        mt_thr = np.float(_opt)
        if 0 <= mt_thr <= 1.0:
            return len([mt[0] for mt in nidx2match_dict.values() if mt[0] >= mt_thr]) / len(nidx2match_dict)
    except:
        pass
    print('\033[31m%s\033[0m' % "Input Error! _opt should in ['avg', 'mid', 'min', 'max'] or a positive decimal!")
    return 0.0


# ---- dissimilarity: get the dissimilarity between two ThemeSLNs from their node-pair similarity matrix ----
# Inputs:
#   1. sim_matrix: the similarity matrix of node-pairs.
#   2. delta: if delta > 0 means using greedy_match_pen to get nidx2match_dict, else use greedy_match
#   3. _opt: refer to _opt in func:match_scores
#   4. _decay: the ratio to decay the redundancy score
def dissimilarity(sim_matrix, base_axis=0, delta=1.0, _opt="avg", _decay=1.0, _tab=""):
    if not isinstance(sim_matrix, np.ndarray) or len(sim_matrix.shape) != 2 or len(sim_matrix) == 0:
        print(_tab + '\033[31m%s\033[0m' % 'Error! The type of the input matrix is not correct!')
        return 0.0
    if type(delta) in [int, float] and delta > 0:
        for_nidx2match = greedy_match_pen(sim_matrix, base_axis, delta, 1.0, _tab)
        back_nidx2match = greedy_match_pen(sim_matrix, 1 - base_axis, delta, 1.0, _tab)
    else:
        for_nidx2match = greedy_match(sim_matrix, base_axis, _tab)
        back_nidx2match = greedy_match(sim_matrix, 1 - base_axis, _tab)
    for_sim = match_scores(for_nidx2match, _opt)
    back_sim = match_scores(back_nidx2match, _opt)
    return 1 - (for_sim + back_sim) / 2.0 * _decay


#######################################################################################
# ------------------- Get Data For Source Text and the Summary ---------------------- #
#######################################################################################
def GetFileCacheDatas(file_fp, dtype='PTrees', pkfile_dir=os.getcwd(), **kwargs):
    type_clr = {'Sents': '32', 'Titles': '32', 'PTrees': '32',
                'titSLNs': '34', 'srcSLNs': '34', 'sumSLNs': '34', 'qrySLNs': '34',
                'TitSLN': '35', 'TopNodeSLN': '35', 'SrcSLN': '35', 'LeadSrcSLN': '35', 'SumSLN': '35', 'QrySLN': '35',
                'sumVecs': '33', 'srcVecs': '33', 'qryVecs': '33', 'sentVecs': '33'}
    tab_str = kwargs.get('_tab', '')
    kwargs['_tab'] = tab_str + '\t'
    fname = os.path.basename(file_fp)
    # ===== check whether the dtype cannot be loaded by this function =====
    if not BoolOR([dtype == cache_type for cache_type in type_clr.keys()]):
        print(tab_str + '\033[31m%s\033[0m' % "The cache data should be in %s" % str(list(type_clr.keys())))
        return None
    if (dtype.lower()).startswith('qry') and 'query' not in map(lambda x: x.lower(), fname.split('.')):
        print(tab_str + '\033[31m%s\033[0m' % ("The file needed to be process is not a query file for " + dtype))
    # ===== If there is no file under file_fp =====
    fplist = GetFileDirPaths(file_fp)[0]
    if not fplist:
        print(tab_str + '\033[31m%s\033[0m' % ("No file found on the path " + file_fp + " ..."))
        return None
    # ===== If the historical cache data exists, just return it ====
    pkfname = '.'.join([fname, dtype, 'pk'])
    data_pkfp = os.path.join(pkfile_dir, pkfname)
    if os.path.isfile(data_pkfp):
        print(tab_str + '\033[' + type_clr[dtype] + 'm%s\033[0m' % ("Loading " + pkfname))
        return Loadpickle(data_pkfp)
    else:
        print(tab_str + '\033[' + type_clr[dtype] + 'm%s\033[0m' % ("Create " + pkfname))
    # == file_fp is a directory for multi-document summary ==
    if len(fplist) > 1:
        # -- initiate cache data --
        if dtype.endswith("SLN"):
            cache_data = ThemeSLN([], [], dtype.rstrip("SLN").lower())
        elif dtype.endswith("Vecs"):
            cache_data = {}
        else:
            cache_data = []
        # -- get cache data for each file and merge them into cache_data --
        for fp in fplist:
            temp_cache = GetFileCacheDatas(fp, dtype, pkfile_dir, **kwargs)
            if dtype.endswith("SLN"):
                cache_data.MergeSLN(temp_cache)
            elif dtype.endswith("Vecs"):
                cache_data.update(temp_cache)
            else:
                cache_data.extend(temp_cache)
        # -- if cache_data has contents, dump it as a pickle --
        if cache_data:
            Dumppickle(data_pkfp, cache_data)
        return cache_data
    # == If only one file contained in file_fp ==
    file_fp = fplist[0] if len(fplist) == 1 else file_fp
    # ==== Create new cache data for current datatype ====
    # ---- Sents/Titles/Parser-Trees ----
    if dtype == 'Sents':
        cache_data = GetSentsList(file_fp, _tab=kwargs['_tab'])
    elif dtype == 'Titles':
        cache_data = GetSrcTitle(file_fp, _tab=kwargs['_tab'])
    elif dtype == 'PTrees':
        sents_list = GetFileCacheDatas(file_fp, "Sents", pkfile_dir, **kwargs)
        cache_data = GetStanfordPTrees(sents_list, _tab=kwargs['_tab'])
    # ---- ThemeSLNs for each sentences within the sentence list ----
    elif dtype == 'titSLNs':
        titles = GetFileCacheDatas(file_fp, 'Titles', pkfile_dir, **kwargs)
        cache_data = BuildSLNforSents(titles, 'title_sent', _tab=kwargs['_tab'])
    elif dtype == 'srcSLNs':
        PTrees = GetFileCacheDatas(file_fp, 'PTrees', pkfile_dir, **kwargs)
        cache_data = BuildSLNforSents(PTrees, 'source_sent', _tab=kwargs['_tab'])
    elif dtype == 'sumSLNs':
        PTrees = GetFileCacheDatas(file_fp, 'PTrees', pkfile_dir, **kwargs)
        cache_data = BuildSLNforSents(PTrees, 'summary_sent', _tab=kwargs['_tab'])
    elif dtype == 'qrySLNs':
        PTrees = GetFileCacheDatas(file_fp, 'PTrees', pkfile_dir, **kwargs)
        cache_data = BuildSLNforSents(PTrees, 'query_sent', _tab=kwargs['_tab'])
    # ---- A ThemeSLN for the whole text ----
    elif dtype == 'TitSLN':
        cache_data = MergeSentsSLN(GetFileCacheDatas(file_fp, "titSLNs", pkfile_dir, _tab=kwargs['_tab']), 'title')
    elif dtype == 'SrcSLN':
        srcSLNs = GetFileCacheDatas(file_fp, 'srcSLNs', pkfile_dir, **kwargs)
        cache_data = MergeSentsSLN(srcSLNs, 'source')
    elif dtype == 'TopNodeSLN':
        sumtype = 'p' if os.path.isfile(file_fp) else 'm'
        nid2tfidf = DatasetNodeTFIDF(pkfile_dir, os.path.dirname(file_fp), sumtype, **kwargs).get(fname, None)
        if nid2tfidf is None:
            print(tab_str + '\033[31m%s\033[0m' % ("No Node TF-IDF is found for the source file " + file_fp + " ..."))
            cache_data = None
        else:
            SrcSLN = GetFileCacheDatas(file_fp, 'SrcSLN', pkfile_dir, **kwargs)
            nid2idx = {node.nid: idx for idx, node in enumerate(SrcSLN.Nodes)}
            topn = min(kwargs.get('topn', 5), len(SrcSLN.Nodes))
            topnids = [nid for (nid, dd) in sorted(nid2tfidf.items(), key=lambda x: x[1]['tfidf'], reverse=True)[:topn]]
            Nodes, Links = [SrcSLN.Nodes[nid2idx[nid]] for nid in topnids], []
            for nid_key in itertools.product(topnids, topnids):
                for link_info in SrcSLN.adj_matrix.get(nid_key, []):
                    templink = ThemeLink(**link_info)
                    templink.l_node = SrcSLN.Nodes[nid2idx[nid_key[0]]]
                    templink.r_node = SrcSLN.Nodes[nid2idx[nid_key[1]]]
                    Links.append(templink)
            cache_data = ThemeSLN(Nodes, Links, type='topnode')
    elif dtype == 'LeadSrcSLN':
        lead_SrcSLN = GetFileCacheDatas(file_fp, 'SrcSLN', pkfile_dir, _tab=kwargs['_tab'])
        lead_SrcSLN.type = "leadsrc"
        nfreq_thr = np.median([node.times for node in lead_SrcSLN.Nodes])
        ld_ratios = kwargs.get('ld_ratios', (0.6, 0.4))
        lead_info_list = GetLeadPKForSrcFile(file_fp, pkfile_dir, len(ld_ratios), _tab=kwargs['_tab'] + "\t")
        cache_data = AddLeadLinks(lead_SrcSLN, lead_info_list, None, nfreq_thr, ld_ratios, _tab=kwargs['_tab'] + "\t")
    elif dtype == 'SumSLN':
        sumSLNs = GetFileCacheDatas(file_fp, 'sumSLNs', pkfile_dir, **kwargs)
        cache_data = MergeSentsSLN(sumSLNs, 'summary')
    elif dtype == 'QrySLN':
        qrySLNs = GetFileCacheDatas(file_fp, 'qrySLNs', pkfile_dir, **kwargs)
        cache_data = MergeSentsSLN(qrySLNs, 'query')
    # ---- Embedding Vectors for nodes and links in ThemeSLN or for sentences ----
    elif dtype == 'sumVecs':
        summarySLN = GetFileCacheDatas(file_fp, 'SumSLN', pkfile_dir, **kwargs)
        cache_data = EmbedNodesLinks(GetLabelGenreTuples(summarySLN, _tab=kwargs['_tab']), 'avg', 0, kwargs['_tab'])
    elif dtype == 'srcVecs':
        sourceSLN = GetFileCacheDatas(file_fp, 'SrcSLN', pkfile_dir, **kwargs)
        cache_data = EmbedNodesLinks(GetLabelGenreTuples(sourceSLN, _tab=kwargs['_tab']), 'avg', 0, kwargs['_tab'])
    elif dtype == 'qryVecs':
        QuerySLN = GetFileCacheDatas(file_fp, 'QrySLN', pkfile_dir, **kwargs)
        cache_data = EmbedNodesLinks(GetLabelGenreTuples(QuerySLN, _tab=kwargs['_tab']), 'avg', 0, kwargs['_tab'])
    elif dtype == 'sentVecs':
        sents_list = GetFileCacheDatas(file_fp, "Sents", pkfile_dir, **kwargs)
        cache_data = EmbedSents2Vectors(sents_list, embopt='avg', stopword=False, _tab=kwargs['_tab'])
    else:
        cache_data = None
    # -- if cache_data has contents, dump it as a pickle --
    if cache_data:
        Dumppickle(data_pkfp, cache_data)
    return cache_data


# ---- Quickly cache Ptrees list pickle for a file by historically parsed Source Files ----
def SpecialForCachePtree(fp, pkdir, base_fn_suffix='.A', add_fn_suffix='.A'):
    fn = os.path.basename(fp)
    print("Quickly cache Ptrees for", fn)
    if os.path.isfile(os.path.join(pkdir, fn + ".PTrees.pk")):
        print("\tHas historical Ptrees for current file")
        return
    print("\tCache Ptrees for current file ...")
    # ---- Load processed sents and ptrees ----
    base_fn = '.'.join(fn.split('.')[:2]) + base_fn_suffix
    try:
        baseSents = Loadpickle(os.path.join(pkdir, base_fn + ".Sents.pk"))
        basePtrees = Loadpickle(os.path.join(pkdir, base_fn + ".PTrees.pk"))
    except Exception:
        print("\t\tNo historical Base-source Sents or PTrees")
        return
    if isinstance(add_fn_suffix, str) and not add_fn_suffix.isspace():
        try:
            addSents = Loadpickle(os.path.join(pkdir, base_fn + add_fn_suffix + ".Sents.pk"))
            addPtrees = Loadpickle(os.path.join(pkdir, base_fn + add_fn_suffix + ".PTrees.pk"))
        except Exception:
            print("\t\tNo historical Additional-summary Sents or PTrees")
            addSents, addPtrees = [], []
        baseSents.extend(addSents)
        basePtrees.extend(addPtrees)
    # ---- Get Ptrees for current file ----
    curSents, curPtrees = GetFileCacheDatas(fp, 'Sents', pkdir, _tab="\t\t"), []
    for cur_sidx, cur_stxt in enumerate(curSents):
        print("\t\t============= SentID:", cur_sidx, "==============")
        find_flag = False
        for b_sidx, b_stxt in enumerate(baseSents):
            if cur_stxt == b_stxt:
                print("\t\t\tFind same sent in BODY! ...")
                baseSents.pop(b_sidx)
                temp_ptree = basePtrees.pop(b_sidx)
                # ---- If temp_ptree is not empty tree, add it into curPtrees list ----
                if len(temp_ptree) > 0:
                    curPtrees.append(temp_ptree)
                    find_flag = True
                    break
        if not find_flag:
            print("\t\t\tCannot find same sent, build the ptree by Stanford Parser ...")
            curPtrees.append(SpecialGetSinglePTree(cur_stxt))
    Dumppickle(os.path.join(pkdir, fn + ".PTrees.pk"), curPtrees)
    return curPtrees


# -------- Get source/summary directory dict, sumtype, filename pattern for AI, ACL, DUC dataset --------
def GetDatasetInfo(dataset="acl", ftype='abs'):
    if dataset == "acl":
        pk_dir, score_dir = acl_pkdir, acl_score_dir
        if ftype not in acl_fsdir:
            print("The ftype should be one in [" + ', '.join(acl_fsdir.keys())+"]!")
            return
        (src_dir, sum_dir, sumtype) = acl_fsdir[ftype]
        fnpt, snpt = acl_fnpt, acl_snpt
        # fnpt, snpt = r"^(P14-1\d{3}\.xhtml)\.A$", r"(P14-1\d{3}\.xhtml)\.A\.(A|W|03)$"
    elif dataset == "ai":
        pk_dir, score_dir = ai_pkdir, ai_score_dir
        if ftype not in ai_fsdir:
            print("The ftype should be one in [" + ', '.join(ai_fsdir.keys()) + "]!")
            return
        (src_dir, sum_dir, sumtype) = ai_fsdir[ftype]
        fnpt, snpt = ai_fnpt, ai_snpt
    elif dataset == "duc":
        pk_dir, score_dir = duc_pkdir, duc_score_dir
        if ftype not in duc_fsdir:
            print("The ftype should be one in [" + ', '.join(duc_fsdir.keys()) + "]!")
            return
        (src_dir, sum_dir, sumtype) = duc_fsdir[ftype]
        if sumtype == 'p':
            fnpt, snpt = duc_fnpt, duc_std_psnpt  # duc_psnpt
        else:
            fnpt, snpt = duc_dirnpt, duc_std_msnpt # duc_msnpt
    else:
        print("The dataset should be one in [\'acl\', \'ai\', \'duc\']!")
        return
    return pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir


def DatasetNodeTFIDF(pk_dir, src_dir, sumtype, _stem=True, _stopw=True, **kwargs):
    # ---- check and load history pickle file ----
    tfidf_pkfp = os.path.join(pk_dir, '_'.join([os.path.basename(src_dir).lower(), 'nid2tfidf',
                                       'stem' if _stem else 'nostem', 'nostopw' if _stopw else 'withstopw']) + ".pk")
    if os.path.isfile(tfidf_pkfp):
        print(kwargs['_tab'] + "Load node TF-IDF for", src_dir)
        return Loadpickle(tfidf_pkfp)
    # ---- cache word frequency for each source file ----
    print(kwargs['_tab'] + "Create node TF-IDF for", src_dir)
    fn2ntf, fn2nlab2nid = {}, {}
    for srcfp in GetFplist(src_dir, sumtype):
        fn = os.path.basename(srcfp)
        SrcSLN = GetFileCacheDatas(srcfp, 'SrcSLN', pk_dir, **kwargs)
        fn2ntf[fn], fn2nlab2nid[fn] = {}, {}
        for node in SrcSLN.Nodes:
            nlab = ' '.join(ProcessTxt2Words(node._label, _stem=_stem, _stopw=_stopw))
            if nlab and not nlab.isspace():
                fn2ntf[fn][nlab] = node.times
                fn2nlab2nid[fn][nlab] = node.nid
    # ---- cache word inverse document frequency ----
    nidfs = Counter()
    for ntfs in fn2ntf.values():
        nidfs.update(ntfs.keys())
    fnum = len(fn2ntf)
    for nlab in nidfs:
        nidfs[nlab] = np.log10(fnum/nidfs[nlab])
    # ---- merge tf with idf for each word in each source file ----
    fn2nid2tfidf = {}
    for fn, ntfs in fn2ntf.items():
        fn2nid2tfidf[fn] = {}
        for nlab, tf in ntfs.items():
            nid = fn2nlab2nid[fn][nlab]
            fn2nid2tfidf[fn][nid] = {'label': nlab, 'tfidf': tf * nidfs.get(nlab, 0)}
    Dumppickle(tfidf_pkfp, fn2nid2tfidf)
    return fn2nid2tfidf


def CacheDatasForDataset(dataset, ftype, quick_ptree=True, **kwargs):
    src_dtypes = ['Sents', 'PTrees', 'Titles', 'TitSLN', 'srcVecs']
    if type(kwargs.get('src_dtypes')) in [list, tuple, set]:
        src_dtypes = kwargs.pop('src_dtypes')

    sum_dtypes = ['Sents', 'PTrees', 'sumVecs']
    if type(kwargs.get('sum_dtypes')) in [list, tuple, set]:
        sum_dtypes = kwargs.pop('sum_dtypes')

    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return

    # ---- Quickly build PTrees for source and summary files for ACL and AI based on processed .A PTrees ----
    if quick_ptree and dataset in ["acl", "ai"]:
        src_ptree_flag = 'PTrees' in src_dtypes
        if src_ptree_flag:
            src_dtypes.remove('PTrees')
        sum_ptree_flag = 'PTrees' in sum_dtypes
        if sum_ptree_flag:
            sum_dtypes.remove('PTrees')
        if src_ptree_flag or sum_ptree_flag:
            src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
            for srcfp in src_sum_fpalign_dict:
                if src_ptree_flag:
                    SpecialForCachePtree(srcfp, pk_dir, '.A', '.A')
                for sumfp in src_sum_fpalign_dict[srcfp]:
                    if sum_ptree_flag:
                        SpecialForCachePtree(sumfp, pk_dir, '.A', '.A')

    # ---- cache src_dtypes and sum_dtypes data ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        for dtype in src_dtypes:
            GetFileCacheDatas(srcfp, dtype, pk_dir, **kwargs)
        for dtype in sum_dtypes:
            for sumfp in src_sum_fpalign_dict[srcfp]:
                GetFileCacheDatas(sumfp, dtype, pk_dir, **kwargs)
    return


def DelCachedData(filepath, pkdir, del_types=[], _tab=""):
    if len(del_types) > 0:
        print(_tab + "Delete cached", ', '.join(del_types), "...")
    for dtype in del_types:
        cache_fp = os.path.join(pkdir, os.path.basename(filepath) + "." + dtype + ".pk")
        if os.path.isfile(cache_fp):
            os.remove(cache_fp)
    return


def CheckEmptyInPTrees(filepath, pk_dir, _new=True, _tab=""):
    ptree_fp = os.path.join(pk_dir, os.path.basename(filepath) + ".PTrees.pk")
    if not os.path.isfile(ptree_fp):
        print(_tab+"No PTrees Files in", os.path.basename(filepath))
        return False
    Ptrees = GetFileCacheDatas(filepath, 'PTrees', pk_dir, _tab=_tab)
    Sents = GetFileCacheDatas(filepath, 'Sents', pk_dir, _tab=_tab+'\t')
    ptree_changed = False
    if len(Sents) != len(Ptrees):
        print(_tab+"\t\tThe number of sentences is not equal to the number of Ptrees")
        return True
    for sidx, sent in enumerate(Sents):
        ptree = Ptrees[sidx]
        if ptree == Tree('ROOT', []):
            print(_tab+"\t\tNo Ptree Sent " + str(sidx) + ", length=" + str(len(sent.split(' '))) + ":", sent)
            if _new:
                temp_ptree = SpecialGetSinglePTree(sent)
                if len(temp_ptree) > 0:
                    print(_tab+"\t\tHave built new ptree for this sentence ....")
                    Ptrees[sidx] = temp_ptree
                    ptree_changed = True
    if ptree_changed:
        Dumppickle(ptree_fp, Ptrees)
    return ptree_changed


# ---- Check the PTrees for each sentences to find the un-parsed sentences ----
def CheckCachedPtrees(dataset, ftype, _new=True, check_src=True, check_sum=True, DelSrcTypes=[], DelSumTypes=[]):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    err_srcfp, err_sumfp = set(), set()
    # ---- Get summary files' path which has error PTrees ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        if check_src and CheckEmptyInPTrees(srcfp, pk_dir, _new):
            err_srcfp.add(srcfp)
        for sumfp in src_sum_fpalign_dict[srcfp]:
            if check_sum and CheckEmptyInPTrees(sumfp, pk_dir, _new):
                err_sumfp.add(sumfp)
    # ---- show error summaries and delete cached data for these summaries ----
    if check_src:
        print("Error Source Files' PTrees (totally", len(err_srcfp), "files):")
        for srcfp in err_srcfp:
            print("\t" + os.path.basename(srcfp))
            if _new:
                DelCachedData(srcfp, pk_dir, DelSrcTypes, _tab="\t")
    if check_sum:
        print("Error Summaries' PTrees (totally", len(err_sumfp), "files):")
        for sumfp in err_sumfp:
            print("\t" + os.path.basename(sumfp))
            if _new:
                DelCachedData(sumfp, pk_dir, DelSumTypes, _tab="\t")
    return


# ---- Check the PTrees for each sentences to find the un-parsed sentences ----
def CheckCachedTitSLN(dataset, ftype, _del=False):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    err_srcfp = set()
    # ---- Get summary files' path which has error PTrees ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        TitSLN = GetFileCacheDatas(srcfp, 'TitSLN', pk_dir)
        # print(srcfp, len(TitSLN))
        if len(TitSLN) == 0:
            err_srcfp.add(srcfp)
    # ---- show error summaries and delete cached data for these summaries ----
    print("No nodes contianed in the TitSLN (totally", len(err_srcfp), "files):")
    for srcfp in err_srcfp:
        print("\t" + os.path.basename(srcfp))
        if _del:
            os.remove(srcfp)
            DelCachedData(srcfp, pk_dir, ['Sents', 'Titles', 'PTrees', 'titSLNs', 'TitSLN', 'srcSLNs', 'SrcSLN', 'srcVecs', 'LeadInfo', 'LeadSrcSLN', 'NodeRanks.title'], _tab="\t\t")
            for sumfp in src_sum_fpalign_dict[srcfp]:
                DelCachedData(sumfp, pk_dir, ['Sents', 'PTrees', 'sumSLNs', 'SumSLN', 'sumVecs', 'fidelity.tit'], _tab="\t\t")
    return


# ---- Compare two Sents list to check whether they are the same ----
def CmpOldNewSents(filepath, pkdir):
    sentsfp = os.path.join(pkdir, os.path.basename(filepath) + ".Sents.pk")
    if os.path.isfile(sentsfp):
        print('\033[32m%s\033[0m' % ("Loading " + sentsfp))
        oldSents = Loadpickle(sentsfp)
        newSents = GetSentsList(filepath, _tab='\t')
        if len(oldSents) == len(newSents):
            return False
        else:
            print("\t\tOld_sentences:", len(oldSents), "New sentences:", len(newSents))
            return True
    print('\033[32m%s\033[0m' % "No old sentence list!" + sentsfp)
    return True


# ---- Update the PTrees list for a file if some sentences in its Sents list is changed ----
def RevisePtreesByNewSents(filepath, pk_dir, _tab=""):
    sent_pkfp = os.path.join(pk_dir, os.path.basename(filepath) + ".Sents.pk")
    ptree_pkfp = os.path.join(pk_dir, os.path.basename(filepath) + ".PTrees.pk")
    newSents = GetSentsList(filepath, _tab=_tab)
    if os.path.isfile(sent_pkfp) and os.path.isfile(ptree_pkfp):
        oldSents = Loadpickle(sent_pkfp)
        oldPTrees = Loadpickle(ptree_pkfp)
        newPTrees = []
        for sent in newSents:
            find_old = False
            for osid, oldsent in enumerate(oldSents):
                if sent == oldsent:
                    find_old = True
                    newPTrees.append(oldPTrees.pop(osid))
                    oldSents.pop(osid)
                    break
            if not find_old:
                newPTrees.append(SpecialGetSinglePTree(sent))
        Dumppickle(ptree_pkfp, newPTrees)
    else:
        os.remove(ptree_pkfp)
        GetFileCacheDatas(filepath, "PTrees", pk_dir, _tab=_tab)
    Dumppickle(sent_pkfp, newSents)
    return


# ---- Check if the sentences in the source file or summary file can be newly splited by the new sent_tokenizer ----
def CheckCachedSents(dataset, ftype, _new=True, check_src=True, check_sum=True, DelSrcTypes=[], DelSumTypes=[]):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    err_srcfp, err_sumfp = set(), set()
    # ---- Align source files with summary files ----
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    for srcfp in src_sum_fpalign_dict:
        if check_src and CmpOldNewSents(srcfp, pk_dir):
            err_srcfp.add(srcfp)
        if check_sum:
            for sumfp in src_sum_fpalign_dict[srcfp]:
                if CmpOldNewSents(sumfp, pk_dir):
                    err_sumfp.add(srcfp)
    # ---- show error summaries and delete cached data for these summaries ----
    if check_src:
        print("Source Files whose sentence list may change:", len(err_srcfp))
        for srcfp in err_srcfp:
            print("\t"+os.path.basename(srcfp))
            if _new:
                print("\t\tChange Sents and PTrees!")
                RevisePtreesByNewSents(srcfp, pk_dir, _tab="\t\t\t")
                DelCachedData(srcfp, pk_dir, DelSrcTypes, _tab="\t")
    if check_sum:
        print("Summary Files whose sentence list may change:", len(err_sumfp))
        for sumfp in err_sumfp:
            print("\t" + os.path.basename(sumfp))
            if _new:
                print("\t\tChange Sents and PTrees!")
                RevisePtreesByNewSents(sumfp, pk_dir, _tab="\t\t\t")
                DelCachedData(sumfp, pk_dir, DelSumTypes, _tab="\t")
    return


#######################################################################################
# ---------------------------------- Test Function ---------------------------------- #
#######################################################################################
def TestSrcSumPathAlign(dataset='acl', ftype='sysC'):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    src_sum_fpalign_dict = AlignSrcSum(src_dir, sum_dir, fnpt, snpt, sumtype)
    align_xml_fp = os.path.join(score_dir, os.path.basename(sum_dir) + "_align_info.xml")
    WriteAlignFileSumXML(src_sum_fpalign_dict, align_xml_fp)


def TestGetSentsList(fp):
    Sents = GetSentsList(fp)
    # ------ show the sentence list -------
    for sidx, sent in enumerate(Sents):
        print(sidx, ":", sent, "\n===============")


def TestStanfordParser(srcfp):
    # # -------- Build Parser Tree for single sentence --------
    # sent = '''The arguments of one EP are linked to the arguments of others either directly (sharing the same variable
    #           as their value), or indirectly (through so-called ‘handle constraints’, where in Fig. 1 denotes equality
    #           modulo quantifier insertion).'''
    # ptree = GetSingleStanfordPTree(sent)
    # print('Sentence:', sent)
    # print(ptree)
    # ptree = GetStanfordPTrees(sent)
    # print('Sentence:', sent)
    # print(ptree)
    # -------- Build Parser Tree for a sentence list --------
    Sents = GetSentsList(srcfp)
    PTrees = GetStanfordPTrees(Sents)
    for sid, sent in enumerate(Sents):
        print("==============================================")
        print('Sentence: %s' % sent)
        print('Parser Tree:', PTrees[sid].height())
        print(PTrees[sid])
        # PTrees[sid].draw()


def TestBuildThemeSLN():
    sents = ['''In this work, we revisit Shared Task 1 from the 2012 * SEM Conference: 
                the automated analysis of negation.''',
             '''Unlike the vast majority of participating systems in 2012, our approach works over explicit and formal 
                representations of propositional semantics, i.e., derives the notion of negation scope assumed 
                in this task from the structure of logical-form meaning representations.''']
    sentsSLN = BuildSLNforSents(sents)
    for sln in sentsSLN:
        sln.showNodes()
        sln.showLinks()
        # sln.showAdjMatrix()


def TestNodeLinkEmbeddings(srcfp):
    sourceSLN = GetFileCacheDatas(srcfp, 'SrcSLN', acl_pkdir)
    label_genre_tuples = GetLabelGenreTuples(sourceSLN)
    EmbedNodesLinks(label_genre_tuples, embopt='avg', stopword=0)


def TestTitleSLN(srcfp):
    # ---- show title SLN ----
    TitSLN = GetFileCacheDatas(srcfp, dtype='TitSLN', pkfile_dir=acl_pkdir)
    # TitSLN.showNodes()
    # TitSLN.showLinks()
    # ---- extend title SLN ----
    SrcSLN = GetFileCacheDatas(srcfp, dtype='SrcSLN', pkfile_dir=acl_pkdir)
    # nid2simnode = FindSameNodes(TitSLN, SrcSLN, 'jcd', 0.9)
    # for nid, (node, sim) in nid2simnode.items():
    #     print(nid, "--", sim, "->", node.nid, ":", node._label)
    # SrcSLN.showLinks()
    exdSLN = ExtendSLN(TitSLN, SrcSLN, scale=1, simtype='jcd', nsim_thr=0.9)
    # exdSLN.showNodes()
    # exdSLN.showLinks()
    DrawSLN(exdSLN, nlabel=False, llabel=False)


def TestSLNSimilarity(srcfp, sumfp, pkdir=acl_pkdir):
    TitSLN = GetFileCacheDatas(srcfp, 'TitSLN', pkdir)
    srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', pkdir)
    # titleSLN.showNodes()
    # titleSLN.showAdjMatrix()

    sumSLNs = GetFileCacheDatas(sumfp, 'sumSLNs', pkdir)
    sumVecs = GetFileCacheDatas(sumfp, 'sumVecs', pkdir)

    print("---------- Abstract -----------")
    for i in range(len(sumSLNs)):
        print("---- Sentence", i, "----")
        nsim_matrix, A_lab2idx, B_lab2idx = GetNodeSim(TitSLN, sumSLNs[i], 'mix', srcVecs, sumVecs, take_freq=False)
        matched_dict = greedy_match_pen(nsim_matrix, 0)
        print("matched value:", match_scores(matched_dict))
        print("matched pairs:")
        for nidx, (mt_score, bidx) in matched_dict.items():
            print(sumSLNs[i].Nodes[nidx]._label, ": ( mt->", mt_score, ", base->", TitSLN.Nodes[bidx]._label, ")")


def TestNodeLinkEmbed(srcfp, pkdir):
    srcVecs = GetFileCacheDatas(srcfp, 'srcVecs', pkdir)
    for cur_tuple in srcVecs.keys():
        print("tuple:", cur_tuple)
        print(srcVecs[cur_tuple])
        print("===============================")


def TestSpecialProcessForCachePtrees():
    # ----------- Build Ptrees for _con and _int source text --------
    srcfp = r"F:\Programs\Eclipse\ReadabilityRating\AI-Dataset\SourceFiles_con\S000437021300043X.xml.C"
    Ptrees = SpecialForCachePtree(srcfp, ai_pkdir)
    Sents = GetFileCacheDatas(srcfp, 'Sents', ai_pkdir)
    for sidx, stxt in enumerate(Sents):
        print(stxt)
        print(Ptrees[sidx])
        print("-----------------------------")
    # ----------- Build Ptrees for _con and _int summmary text --------
    sumfp = r"F:\Programs\Eclipse\ReadabilityRating\AI-Dataset\Summary_con\S000437021300043X.xml.C.B"
    Sents = GetFileCacheDatas(sumfp, 'Sents', ai_pkdir)
    Ptrees = SpecialForCachePtree(sumfp, ai_pkdir)
    for sidx, stxt in enumerate(Sents):
        print(stxt)
        print(Ptrees[sidx])
        print("-----------------------------")


def CheckQRYSents():
    for fp in GetFileDirPaths(qry_fdir, depth=2)[0]:
        sent_list = GetFileCacheDatas(fp, 'Sents', qry_pkdir)
        # print(os.path.basename(fp), "---- SentNum:", len(sent_list))
        if len(sent_list) < 10:
            print(fp, "---- SentNum:", len(sent_list))


def DelCachedDataByTime(dataset, ftype, Deltypes, basetype='PTrees', basetm=['2020', '08', ['21', '22']]):
    try:
        pk_dir, src_dir, sum_dir, sumtype, fnpt, snpt, score_dir = GetDatasetInfo(dataset, ftype)
    except:
        return
    src_fplist, temp_dirlist = GetFileDirPaths(src_dir, depth=2)
    for srcfp in src_fplist:
        ptree_fp = os.path.join(pk_dir, '.'.join([os.path.basename(srcfp), basetype, "pk"]))
        if not os.path.isfile(ptree_fp):
            continue
        lctime = time.localtime(os.stat(ptree_fp).st_mtime)
        y, m, d = time.strftime('%Y', lctime), time.strftime('%m', lctime), time.strftime('%d', lctime)
        print(os.path.basename(ptree_fp), y, m, d)
        if y == basetm[0] and m == basetm[1] and d in basetm[2]:
            for dtype in Deltypes:
                cache_fp = os.path.join(pk_dir, os.path.basename(srcfp) + "." + dtype + ".pk")
                if os.path.isfile(cache_fp):
                    print("\tDelete cached " + dtype + " ...")
                    os.remove(cache_fp)
    return


#######################################################################################
# ---------------------------------- Main function ---------------------------------- #
#######################################################################################
if __name__ == "__main__":
    # TestSrcSumPathAlign('duc', 'p100')
    # TestGetSentsList(sumfp)
    # TestStanfordParser(sumfp)
    # TestBuildThemeSLN()
    # TestTitleSLN(srcfp)
    # TestSLNSimilarity(srcfp, sumfp)
    # TestNodeLinkEmbeddings()
    # for dataset in ['duc']:
    #     for ftype in ['m100']:
    #         CacheDatasForDataset(dataset, ftype, quick_ptree=False, src_dtypes=['srcVecs'], sum_dtypes=[])
    # CheckCachedSents('ai', 'abs', _new=False, check_src=True, check_sum=True, DelSrcTypes=['srcSLNs', 'SrcSLN',
    #                  'LeadInfo', 'LeadSrcSLN', 'NodeRanks.title'], DelSumTypes=['sumSLNs', 'SumSLN'])
    # CheckCachedPtrees('duc', 'p100', _new=False, check_src=True, check_sum=False, DelSrcTypes=[], DelSumTypes=[])
    TopNodeSLN = GetFileCacheDatas(r"F:\ReadabilityRating\ACL-Dataset\SourceFiles_abs\P14-1009.xhtml.A", 'TopNodeSLN', acl_pkdir)
    TopNodeSLN.showNodes()
    TopNodeSLN.showLinks()