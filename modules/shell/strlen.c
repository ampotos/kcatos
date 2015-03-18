int kstrlen(const char *s){
  register int  i = 0;
  register char *t = (char *)s;
  while (*t++) ++i;
  return i;
}
