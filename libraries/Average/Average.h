#ifndef Average_h
#define Average_h

class Average
{
	public:
	Average(int numReadings);
		void update(int newReading);
		int  getAverage();

	private:
		int numReadings;
		int readings[];
		int currentIndex = 0;
		int total        = 0;
		int average      = 0;

		void addReading(int newReading);
};

#endif
