class my_queue
{
	private:
		datatype q[maxsize];
		int Front,Rear;
	public:
		bool empty(){return Rear==Front;}
		int size(){return Rear-Front;}
		void push(datatype tmp)
		{
			q[Rear]=tmp;
			Rear++;
		}
		void pop(){Front++;}
		datatype front(){return q[Front];}
		datatype rear(){return q[rear];}
		void clear(){Front=0;Rear=0;}
};
