// klasa Timer

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
            (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};

double avg(double t[], int n)			// pomocniczo do uśredniania wyników
{
	double sum = 0.0;
	int i;
	for (i = 0; i < n; i++) sum += t[i];
	return sum/n;
}
