#include"utilities.hpp"

#include<thread>
#include<cmath>

namespace Yazh::Core {
	void sleep(f64 ms) {

		static f64 estimate = 5e6;
		static f64 mean = 5e6;
		static f64 m2 = 0;
		static u64 count = 1;

		while (ms > estimate) {
			auto start = std::chrono::high_resolution_clock::now();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::nanoseconds observed = end - start;
			ms -= observed.count() / 1e6;

			++count;
			f64 delta = observed.count() - mean;
			mean += delta / count;
			m2 += delta * (observed.count() - mean);
			f64 stddev = sqrt(m2 / (count - 1));
			estimate = mean + stddev;
		}

		// spin lock
		auto start = std::chrono::high_resolution_clock::now();
		while ((std::chrono::high_resolution_clock::now() - start).count() / 1e6 < ms);
	}
} // namespace Yazh::Core
