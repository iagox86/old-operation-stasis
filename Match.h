// Match.h
// by iago
// Sept. 10/2003
//
// These are basically functions for pattern-matching and replacing

#ifndef MATCH_H
#define MATCH_H

bool Replace(const char *Find, const char *Replace, char *String);
bool ReplaceAll(const char *Find, const char *ReplaceChar, char *String);


int Match(const char *mask, const char *name);
inline char *RemoveSingleChar(char *String, int Location);
inline char *InsertSingleChar(char *String, int Location, char Char);
bool ReplaceAll(const char *Find, const char *ReplaceChar, char *String);
bool Replace(const char *Find, const char *Replace, char *String);

#endif