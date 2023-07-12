
namespace Yazh::Core {
    inline f64 getAbsoluteTime() {
		return std::chrono::steady_clock::now().time_since_epoch() / std::chrono::seconds(1);
	}
} // namespace Yazh::Core