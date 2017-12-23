//
// Created by sheng on 2017/12/16.
//

#ifndef MYRPC_MC_EPOLLER_H
#define MYRPC_MC_EPOLLER_H

    class MC_Epoller{

    public:
        MC_Epoller(bool bEt= true);
        ~MC_Epoller();

        create(int max_connections);
        add(int fd,long long data, uint32 event);
        mod(int fd,long long data, uint32 event);
        del(int fd,long long data,uint32 event);
        wait(int millsecond);

        struct eppll_event& get(int i){

        }


    protected:

        int _iEpollfd;

        int _max_connections;

        struct epoll_event *_pevs;

        bool _et;

    };


#endif //MYRPC_MC_EPOLLER_H
