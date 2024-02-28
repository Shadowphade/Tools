import requests
import sys
import os
from html.parser import HTMLParser

links = []

class ParseLinks(HTMLParser):
    def handle_starttag(self, tag, attrs):
        if tag != 'a':
            return
        attr = dict(attrs)
        links.append(attr)

        return None;

def getDirectory(path):
    responce = requests.get(path)
    links.clear()
    parse = ParseLinks();
    links.append(parse.feed(responce.text))


def recurse(path, filePath, depth):
    getDirectory(path)
    if(depth <= 0): return
    linkStrings = []
    dirStrings = []
    fileStrings = []

    for link in links:
        if(link != None): linkStrings.append(link.get('href'))

    for link in linkStrings:
        if "/" in link: dirStrings.append(link)
        if "?" in link: continue
        fileStrings.append(link)

    dirStrings.pop(0)
    print("Depth: " + str(depth) + " Strings: " + str(dirStrings))
    if len(dirStrings) == 0 and len(fileStrings) == 0: return

    for direc in dirStrings:
        newPath = path + direc
        newDir = filePath + direc
        print("File" + newDir + "\t link: " + newPath)
        os.system('mkdir -p ' + filePath + direc)
        recurse(newPath, (filePath + direc), depth - 1)

    for files in fileStrings:
         os.system('wget ' + path + files + " -P " + filePath)


def main():
    args = sys.argv[1:]
    if len(args) < 2 : print("Usage: stupidScraper <link to scrape> <path to put data>")
    currentLink = args[0]
    path = args[1]
    if !(path.endswith("/")) : path.append("/")
    recurse(currentLink, path, 50)

if __name__ == '__main__':
    main()
