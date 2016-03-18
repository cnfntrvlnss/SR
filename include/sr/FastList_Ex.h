#ifndef FASTLIST_EX__H
#define FASTLIST_EX__H

#include "FastList.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZSR's work: add some tools to extend functionality.

#include <list>
template<typename TYPE, typename ARG_TYPE>
void cfastlist_sort(CFastList<TYPE, ARG_TYPE> &cli)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort();
	POSITION po = cli.GetHeadPosition();
	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		cli.SetAt(po, *it);
		cli.GetNext(po);
	}
}

template<typename TYPE, typename ARG_TYPE, typename Compare>
void cfastlist_sort(CFastList<TYPE, ARG_TYPE> &cli, Compare comp)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort(comp);
	POSITION po = cli.GetHeadPosition();
	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		cli.SetAt(po, *it);
		cli.GetNext(po);
	}
}

template<typename TYPE, typename ARG_TYPE, typename Compare>
void cfastlist_sort_copy(const CFastList<TYPE, ARG_TYPE> &cli, CFastList<TYPE, ARG_TYPE> &desli, Compare comp)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort(comp);

	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		desli.AddTail(*it);
	}
}

#endif