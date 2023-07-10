#include"utilities.hpp"

#include<thread>
#include<cmath>

namespace Yazh {
	f64 getAbsoluteTime() {
		return std::chrono::steady_clock::now().time_since_epoch() / std::chrono::seconds(1);
	}

	void sleep(f64 ms) {
		using nano = std::chrono::nanoseconds;
		using milli = std::chrono::milliseconds;
		using clock = std::chrono::high_resolution_clock;

		static f64 estimate = 5e6;
		static f64 mean = 5e6;
		static f64 m2 = 0;
		static u64 count = 1;

		while (ms > estimate) {
			auto start = clock::now();
			std::this_thread::sleep_for(milli(1));
			auto end = clock::now();

			nano observed = end - start;
			ms -= observed.count() / 1e6;

			++count;
			f64 delta = observed.count() - mean;
			mean += delta / count;
			m2 += delta * (observed.count() - mean);
			f64 stddev = sqrt(m2 / (count - 1));
			estimate = mean + stddev;
		}

		// spin lock
		auto start = clock::now();
		while ((clock::now() - start).count() / 1e6 < ms);
	}
}
