#ifndef __AUTOCOMPLETE_HPP__
#define __AUTOCOMPLETE_HPP__
// init
vector<string> commands={"comp","help","run","quit","test","clear","cat","clean"};
vector<string> files={"ans","data","my","all"};
vector<string> current_map;
char *command_generator(const char *text,int state)
{
    static int list_index,len;
    string name;
    if(!state) {
        list_index=0;
        len=strlen(text);
    }
    while(list_index<current_map.size()){
        name=current_map[list_index++];
        if (strncmp(name.c_str(), text, len) == 0){
            char *t;
            t=(char*)malloc(name.size()+1);
            strcpy(t,name.c_str());
            return t;
        }
    }
    return (char *)NULL;
}
char **autoComplete(const char *text,int start,int end)
{
    char **matches;
    matches=(char**)NULL;
    if(start==0) current_map=commands;
    else current_map=files;
    matches=rl_completion_matches(text,command_generator);
    return matches;
}
void init(){
    rl_attempted_completion_function=autoComplete;
}
#endif