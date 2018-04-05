struct heap
{
	data arr[100011];
	int heap_size;
	heap()
	{
		memset(arr,0,sizeof(data));
		heap_size=0;
	}
	int size()
	{
		return heap_size;
	}
	bool empty()
	{
		return heap_size>0;
	}
	data top()
	{
		return arr[1];
	}
	void push(data x)
	{
		arr[++heap_size]=x;
		int i=heap_size;
		while(i!=1&&arr[i/2]<arr[i])
		{
			swap(arr[i],arr[i/2]);
			i=i/2;
		}
	}
	data pop()
	{
		data ans=arr[1];
		arr[1]=arr[heap_size];
		heap_size--;
		int i=1;
		while(i*2<=heap_size&&arr[i]<arr[i*2]||i*2+1<=heap_size&&arr[i]<arr[i*2+1])
		{
			if(arr[i*2+1]<arr[i*2])
			{
				swap(arr[i*2],arr[i]);
				i=i*2;
			}
			else if(arr[i*2]<arr[i*2+1])
			{
				swap(arr[i*2+1],arr[i]);
				i=i*2+1;
			}
		}
		return ans;
	}
};
