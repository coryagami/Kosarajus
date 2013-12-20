class DisjointSet    
{
public:
	DisjointSet() { DisjointSet(0); }

	// constructor to make disjoint set with N single sets
    DisjointSet(int N)   
	{
		cnt = N;
		setRep = new int[N];
		setSize = new int[N];
        for(int i=0; i<N; i++)	
		{
			setRep[i] = i;
			setSize[i] = 1;
		}
    }

	// destructor 
    ~DisjointSet()	
	{
		delete [] setRep;
		delete [] setSize;
    }

	// Return the representative node of the set with 'x' in it
    int find(int x)	
	{
		int root = x;
		while (root != setRep[root])
			root = setRep[root];
		while (x != root) 
		{
			int newx = setRep[x];
			setRep[x] = root;
			x = newx;
		}
		return root;
    }

	// merge sets with x and y and remove old sets iff they are 
	// already in different sets
    void merge(int x, int y)
	{
		int i = find(x);
		int j = find(y);
		if (i == j) return;
		
		// make smaller root point to larger one
        if(setSize[i] < setSize[j])	
		{ 
			setRep[i] = j; 
			setSize[j] += setSize[i]; 
		} 
		else
		{ 
			setRep[j] = i; 
			setSize[i] += setSize[j]; 
		}
		cnt--;
	}

	// returns true if x and y are in the same set (same find())
	bool connected(int x, int y)    
	{
		if(find(x) == find(y))
			return true;
		return false;
	}

	// returns the total number of sets in teh disjoins set
	int count() 
	{
		return cnt;
	}

	// returns size of specific set containing x
	int getSetSize(int x) 
	{
		return setSize[x];
	}

	// iterates through all subsets and returns size of the maximum set
	// or, the number of nodes!
	int getmaxSetSize() 
	{
		int maxSize = 0;
		for(int i=0; i<cnt; i++)
			if(setSize[i] > maxSize)
				maxSize = setSize[i];
		return maxSize;
	}

	// returns the representative node of the largest set, for comparing
	// against to find edge count!
	int getmaxSetSizeNode() 
	{
		int maxNode = 0;
		for(int i=0; i<cnt; i++)
			if(setSize[i] > setSize[maxNode])
				maxNode = i;
		return maxNode;
	}
	private:
		int *setRep, cnt, *setSize;
};