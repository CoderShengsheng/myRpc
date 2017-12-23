//
// Created by sheng on 2017/12/16.
//

#include "mc_epoller.h"

MC_Epoller::MC_Epoller(bool bEt) {
    _iEpollFfd          =-1;
    _max_connections    =1024;
    _et                 =bEt;
    _pevs               =NULL;

}

MC_Epoller::~MC_Epoller() {
    if(_pevs!=NULL){
        delete[] _pevs;
        _pevs=NULL;
    }

    if(_iEpollFfd>=0){
        close(_iEpollFfd);
    }
}

void MC_Epoller::ctrl(int fd, long long data, uint32 events, int op) {
    struct epoll_event ev;
    ev.data.u64=data;
    if(_et)
    {
        ev.events=events | EPOLLET;
    }
    else
    {
        ev.events=events;
    }

    epoll_ctl(_iEpollFfd,op,fd,&ev);
}

void MC_Epoller::create(int max_connections) {

    _max_connections=max_connections;
    _iEpollFfd=epoll_create(_max_connections+1);
    if(_pevs!=NULL){
        delete[] _pevs;
    }

    _pevs= new epoll_event[_max_connections+1];

}

void MC_Epoller::add(int fd, long long data, uint32 event) {
    ctrl(fd,data,event,EPOLL_CTL_ADD);
}

void MC_Epoller::mod(int fd, long long data, uint32 event) {
    ctrl(fd,data,event,EPOLL_CTL_MOD);
}

void MC_Epoller::del(int fd, long long data, uint32 event) {
    ctrl(fd,data,event,EPOLL_CTL_DEL);
}

void MC_Epoller::wait(int millsecond) {
    return epoll_wait(_iEpollFfd,_pevs,_max_connections+1,millsecond);
}
