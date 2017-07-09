#pragma once
#include<vector>
#include<iostream>
#include<queue>
#include<assert.h>
#include"UnionFindSet.h"
using namespace std;


template<class W>
struct LinkEdge
{
	W _weight;
	size_t _srcIndex;
	size_t _desIndex;
	LinkEdge<W>*_pNext;
	LinkEdge(const W&weight, size_t srcIndex, size_t desIndex)
		: _weight(weight)
		, _srcIndex(srcIndex)
		, _desIndex(desIndex)
		, _pNext(NULL)
	{}
};


template<class V,class W>
class GraphLink
{
public:

	GraphLink(bool IsDirect = false)
		:_IsDirect(false)
	{}


	GraphLink(const V*pVer, size_t size, bool IsDirect = false)
		:_IsDirect(IsDirect)
	{
		_vex.resize(size);
		_LinkTable.resize(size, NULL);
		for (size_t idx = 0; idx < size; ++idx)
		{
			_vex[idx] = pVer[idx];
		}
	}

	void AddEdge(const V&v1, const V&v2, const W&weight)
	{
		size_t srcIdx = GetIndexOfvertex(v1);
		size_t desIdx = GetIndexOfvertex(v2);
		//assert(srcIdx != desIdx);
		if (_IsDirect)
		{
			_AddEdge(srcIdx, desIdx, weight);
		}
		else
		{
			_AddEdge(srcIdx, desIdx, weight);
			_AddEdge(desIdx, srcIdx, weight);
		}
	}

	size_t GetIndexOfvertex(const V&v)
	{
		for (size_t idx = 0; idx < _vex.size(); ++idx)
		{
			if (_vex[idx] == v)
				return idx;
		}
		assert(false);
		return -1;
	}

	size_t GetDev(const V&v)
	{
		size_t srcIdx = GetIndexOfvertex[v];
		LinkEdge<W>*pEdge = _LinkTable[srcIdx];
		size_t count = 0;
		while (pEdge)
		{
			count++;
			pEdge = pEdge->_pNext;
		}
		fot(size_t idx = 0; idx < _LinkTable.size(); ++idx)
		{
			if (srcIdx != idx)
			{
				pEdge = _LinkTable[idx];
				while (pEdge)
				{
					if (pEdge->_desIdx == srcIdx)
					{
						count++;
						break;
					}
					pEdge = pEdge->_pNext;
				}
			}
		}
		return count;
	}


	void BFS(const V&v)
	{
		vector<bool>visited(_vex.size(), false);
		size_t index = GetIndexOfvertex(v);
		for (size_t idx = 0; idx < _vex.size(); ++idx)
		{
			if (!visited[idx])
				_BFS(_vex[idx], visited);
		}
		cout << "NULL" << endl;
	}

	void DFS(const V&v)
	{
		size_t index = GetIndexOfvertex(v);
		vector<bool>visited(_vex.size(), false);
		_DFS(index, visited);
		for (size_t idx = 0; idx < _vex.size(); ++idx)
		{
			_DFS(idx, visited);
		}
		cout << "NULL" << endl;
	}
	pair<GraphLink<V, W>, bool>GetminTree()
	{
		GraphLink<V, W>g;
		g._vex = _vex;
		g._LinkTable.resize(_vex.size(), NULL);
		g._IsDirect = false;
		vector<LinkEdge<W>*>edges;
		for (size_t idx = 0; idx < _LinkTable.size(); ++idx)
		{
			LinkEdge<W>*pCur = _LinkTable[idx];
			while (pCur)
			{
				if (pCur->_srcIndex<pCur->_desIndex)
					edges.push_back(pCur);
				pCur = pCur->_pNext;
			}
		}
		struct Compare
		{
			bool operator()(const LinkEdge<W>*pLeft, const LinkEdge<W>*pRight)
			{
				return pLeft->_weight < pRight->_weight;
			}
		};
		sort(edges.begin(), edges.end());
		UnionFindSet ufs(_vex.size());
		size_t count = 0;
		LinkEdge<W>*pedge;
		for (size_t idx = 0; idx < edges.size(); ++idx)
		{
			pedge = edges[idx];
			ufs.Union(pedge->_srcIndex, pedge->_desIndex);
			if (!ufs.IsSameSet(pedge->_srcIndex, pedge->_desIndex))
			{
				g.AddEdge(_vex[pedge->_srcIndex], _vex[pedge->_desIndex], _vex[pedge->_weight]);
				count++;
				if (count == _vex.size())
					return make_pair(g, true);
			}
		}
		return make_pair(g, false);
	}


private:

	void _DFS(size_t index, vector<bool>&visited)
	{
		if (!visited[index])
		{
			cout << _vex[index] << "-->";
			visited[index] = true;
		}
		LinkEdge<W>*pCur = _LinkTable[index];
		while (pCur)
		{
			if (!visited[pCur->_desIndex])
				_DFS(pCur->_desIndex, visited);
			pCur = pCur->_pNext;
		}
	}

	void _BFS(const V&v, vector<bool>&visited)
	{
		queue<size_t>q;
		q.push(GetIndexOfvertex(v));
		while (!q.empty())
		{
			size_t front = q.front();
			q.pop();
			if (!visited[front])
			{
				cout << _vex[front] << "-->";
				visited[front] = true;
				LinkEdge<W>*pCur = _LinkTable[front];
				while (pCur)
				{
					if (visited[pCur->_desIndex])
						q.push(pCur->_desIndex);
					pCur = pCur->_pNext;
				}
			}
		}
	}

	void _AddEdge(size_t srcIdx, size_t desIdx, const W&weight)
	{
		LinkEdge<W> *pEdge = new LinkEdge<W>(weight, srcIdx, desIdx);
		pEdge->_pNext = _LinkTable[srcIdx];
		_LinkTable[srcIdx] = pEdge;
	}

private:
	std::vector<V>_vex;
	bool _IsDirect;
	std::vector<LinkEdge<W>*> _LinkTable;
};

