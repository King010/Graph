
#pragma once
#include<vector>
#include<iostream>
using namespace std;

template<class V,class W>
class GraphMatrix
{

public:
	GraphMatrix(const V* pVer, size_t size, bool IsDirect)
		:_IsDirect(IsDirect)
	{
		_ver.resize(size);
		_edge.resize(size);
		for (size_t idx = 0; idx < size; ++idx)
		{
			_ver[idx] = pVer[idx];
			_edge[idx].resize(size);
		}
	}

	void AddEdge(const V&v1,const V&v2,const W&weight)
	{
		size_t row = GetIndexOfvertex(v1);
		size_t col = GetIndexOfvertex(v2);

		if (_IsDirect)
		{
			_edge[row][col] = weight;
		}
		else
		{
			_edge[row][col] = weight;
			_edge[col][row] = weight;
		}
	}

	size_t GetIndexOfvertex(const V&v)
	{
		for (size_t idx = 0; idx < _ver.size(); ++idx)
		{
			if (_ver[idx] == v)
				return idx;
		}
		assert(false);
		return -1;
	}

private:
	std::vector<V> _ver;
	bool _IsDirect;
	std::vector<vector<W>> _edge;
};
