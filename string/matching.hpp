#pragma once

#include <string.h>

void getNext(char *s, int *next){
    int i = -1, j = 0;
    int slen = strlen(s);
    next[0] = -1;
    while(j < slen){
        if(i < 0 || s[i] == s[j])
            next[++j] = ++i;
        else
            i = next[i];
    }
}

int kmpSearch(char *s, char *t, int *next){
    int i = 0, j = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    while(i < tlen && j < slen){
        if(i < 0 || s[j] == t[i])
            ++i, ++j;
        else
            i = next[i];
    }
    if(i >= tlen)
        return j-tlen;
    return -1;
}

void charReverseDistance(char *s, int *p, int plen){
    int slen = strlen(s);
    int mxmv = slen + 1;
    for(int i = 0;i < plen;i++)
        p[i] = mxmv;
    for(int i = slen-1;i >= 0;i--)
        if(p[s[i]] == mxmv)
            p[s[i]] = slen-i;
}

int sundaySearch(char *s, char *t){
    int slen = strlen(s);
    int tlen = strlen(t);
    int ps = 0, pt = 0, pp = 0;
    int p[256];
    charReverseDistance(t, p, 256);
    while(pt < tlen && pp < slen-tlen){
        if(s[ps] == t[pt])
            ++ps, ++pt;
        else{
            pp += p[s[pp+tlen]];
            ps = pp;
            pt = 0;
        }
    }
    if(pt >= tlen)
        return pp;
    return -1;
}