#include <iostream>
#include <functional>
#include <typeindex>
#include <vector>
#include <unordered_map>
#include <any>

#define endl '\n'

using namespace std;

enum class UserEvent { LOGIN = 0 };
enum class DataEvent { CREATED = 0 };

/// <summary>
/// 커스텀 해시 함수
/// </summary>
struct PairHash {
	template<typename T1, typename T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto h1 = hash<T1>{}(p.first);
		auto h2 = hash<T2>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

/// <summary>
/// 통합 이벤트 버스
/// </summary>
class UnifiedEventBus {
	using typeIdx = pair<type_index, int>;
private:
	unordered_map<typeIdx, vector<function<void(const any&)>>, PairHash> subscribers;

public:
	template<typename EventEnum, typename DataType>
	void subscribe(EventEnum eventType, function<void(const DataType&)> callback) {
		auto key = make_pair(type_index(typeid(EventEnum)), static_cast<int>(eventType));
		subscribers[key].emplace_back([callback](const any& data) {
			try {
				callback(any_cast<const DataType&>(data));
			}
			catch (const bad_any_cast&) {
				cerr << "Type mismatch!" << endl;
			}
			});
	}

	template<typename EventEnum>
	void subscribe(EventEnum eventType, function<void()> callback) {
		auto key = make_pair(type_index(typeid(EventEnum)), static_cast<int>(eventType));
		subscribers[key].emplace_back([callback](const any&) {
			callback();
			});
	}

	template<typename EventEnum, typename DataType>
	void publish(EventEnum eventType, const DataType& data) {
		auto key = make_pair(type_index(typeid(EventEnum)), static_cast<int>(eventType));
		if (subscribers.find(key) != subscribers.end()) {
			any anyData = data;
			for (auto& callback : subscribers[key]) callback(anyData);
		}
	}

	template<typename EventEnum>
	void publish(EventEnum eventType) {
		auto key = make_pair(type_index(typeid(EventEnum)), static_cast<int>(eventType));

		if (subscribers.find(key) != subscribers.end()) {
			any emptyData;
			for (auto& callback : subscribers[key]) callback(emptyData);
		}
	}
};

int main() {
	UnifiedEventBus bus;

	bus.subscribe(UserEvent::LOGIN, []() {cout << "UserEvent::LOGIN" << endl; });
	bus.subscribe(DataEvent::CREATED, []() {cout << "DataEvent::CREATED" << endl; });

	bus.publish(UserEvent::LOGIN);
	bus.publish(DataEvent::CREATED);
	return 0;
}