#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>

using namespace std;

#define cout std::cout
#define endl '\n'
#define SIZE 7

using diPair = pair<double, int>;
using diPair2D = vector<vector<diPair>>;
using double2D = double[SIZE][SIZE];
using distAndCoord = tuple<double, int, int>;

enum NODE
{
	A, B, C, D, E, F, G
};

void ConnectNode(vector<distAndCoord>& roads, diPair2D& graph)
{
	for (auto [dist, u, v] : roads)
	{
		graph[u].emplace_back(dist, v);
		graph[v].emplace_back(dist, u);
	}
}

void SetSpeedMap(double2D speedMap, vector<distAndCoord>& speeds)
{
	for (auto [speed, u, v] : speeds)
	{
		speedMap[u][v] = speed; // u->v 로의 속도
	}
}

string GetTimeInHMS(double sec)
{
	int secInt = static_cast<int>(sec);
	string res = "";
	int newHour = secInt / 3600;
	secInt %= 3600;
	int newMin = secInt / 60;
	int newSec = secInt % 60;

	res += to_string(newHour) + "시간 " + to_string(newMin) + "분 " + to_string(newSec) + "초";
	return res;
}

/// <summary>
/// 속도 포함 다익스트라
/// </summary>
/// <param name="graph">각 지점 간 거리</param>
/// <param name="speedMap">각 지점 간 속도</param>
/// <param name="start">시작점</param>
/// <param name="end">도착점</param>
/// <returns></returns>
double Dijkstra(diPair2D& graph, double2D& speedMap, int start, int end, bool isSpeed = false)
{
	priority_queue<diPair, vector<diPair>, greater<diPair>> q;
	vector<double> g(SIZE, DBL_MAX); // 누적 시간 배열, 시작 지점 제외 전부 INF로 고정
	vector<int> prevs(SIZE, -1); // 이전 노드 주소 저장

	g[start] = 0.0; // 시작 지점 시간 = 0
	string typeMessages[] = { "거리", "시간" };
	string unitMessages[] = { "km", "초" };
	q.emplace(0.0, start);

	while (!q.empty())
	{
		auto [curG, u] = q.top();
		q.pop();

		printf("현재 정점: %c\n", u + 'A');
		if (u == end) // 다익스트라 알고리즘과의 유일한 차이 => 목적지에 도달하면 break
		{
			printf("도착 완료\n");
			break;
		}

		printf("누적 %s: ", typeMessages[isSpeed].c_str());

		if (isSpeed) printf("%s\n", GetTimeInHMS(g[u]).c_str());
		else printf("%.3g%s\n", g[u], unitMessages[isSpeed].c_str());

		if (curG > g[u]) continue;

		for (auto [d, node] : graph[u])
		{
			if (prevs[u] == node) continue;

			double val = 0.0;

			if (isSpeed)
			{
				double speed = speedMap[u][node]; // u~node까지 속도
				printf("%c~%c까지 거리: %.3gkm, 속도: %.3gkm/h\n", u + 'A', node + 'A', d, speed);
				val = d / speed * 3600; // 초로 계산
			}
			else val = d;

			double newG = val + g[u];

			printf("%c까지 누적 %s: ", node + 'A', typeMessages[isSpeed].c_str());

			if (isSpeed) printf("%s", GetTimeInHMS(newG).c_str());
			else printf("%.3g%s", newG, unitMessages[isSpeed].c_str());

			if (g[node] > newG) // 기존 누적 거리 > 현재 노드 누적 거리 + 다음 노드 거리면 갱신
			{
				g[node] = newG;
				prevs[node] = u;

				q.emplace(newG, node);
				printf(" O\n");
			}
			else
			{
				printf(" X\n");
			}
		}
		cout << endl;
	}

	int arrive = end;

	printf("역추적: %c ", arrive + 'A');
	arrive = prevs[arrive];

	while (arrive != -1)
	{
		printf("- %c ", arrive + 'A');
		arrive = prevs[arrive];
	}
	cout << endl;
	return g[end];
}

/// <summary>
/// 일반 다익스트라
/// </summary>
/// <param name="graph">각 지점 간 거리</param>
/// <param name="start">시작점</param>
/// <param name="end">도착점</param>
/// <returns></returns>
double Dijkstra(diPair2D& graph, int start, int end)
{
	double2D speedMap = {};
	return Dijkstra(graph, speedMap, start, end);
}

double Astar(diPair2D& graph, double2D& speedMap, int start, int end, vector<double>& h, bool isSpeed = false)
{
	priority_queue<diPair, vector<diPair>, greater<diPair>> q;
	vector<double> g(SIZE, DBL_MAX); // 누적거리 배열, 시작 지점 제외 전부 INF로 고정
	vector<int> prevs(SIZE, -1); // 이전 노드 주소 저장

	g[start] = 0.0; // 시작 지점 거리 = 0
	string typeMessages[] = { "거리", "시간" };
	string unitMessages[] = { "km", "초" };

	double fisrtF = h[start];

	if (isSpeed)
	{
		fisrtF *= 3600 / 15; // 휴리스틱 거리 * 3600(초) / 15km/s 
	}
	q.emplace(fisrtF, start);

	while (!q.empty())
	{
		auto [curF, u] = q.top();
		q.pop();

		printf("-----------------------------\n");
		printf("현재 정점: %c\n", u + 'A');
		if (u == end) // 다익스트라 알고리즘과의 유일한 차이 => 목적지에 도달하면 break
		{
			printf("도착 완료\n");
			break;
		}

		printf("예상 %s: ", typeMessages[isSpeed].c_str());

		if (isSpeed) printf("%s\n", GetTimeInHMS(curF).c_str());
		else printf("%.3g%s\n", curF, unitMessages[isSpeed].c_str());

		for (auto [d, node] : graph[u])
		{
			if (prevs[u] == node) continue;

			double val = 0.0;

			if (isSpeed)
			{
				double speed = speedMap[u][node];
				printf("%c~%c까지 거리: %.3gkm, 속도: %.3gkm/h\n", u + 'A', node + 'A', d, speed);
				val = d / speed * 3600; // 초로 계산
			}
			else val = d;

			printf("%c까지 누적 %s: ", node + 'A', typeMessages[isSpeed].c_str());

			double newG = val + g[u];

			if (isSpeed) printf("%s\n", GetTimeInHMS(newG).c_str());
			else printf("%.3g%s\n", newG, unitMessages[isSpeed].c_str());
			
			double newH = h[node];

			if (isSpeed) newH *= 3600 / 15;

			printf("%c에서 도착까지 추정 %s: ", node + 'A', typeMessages[isSpeed].c_str());

			if (isSpeed) printf("%s\n", GetTimeInHMS(newH).c_str());
			else printf("%.3g%s\n", newH, unitMessages[isSpeed].c_str());

			printf("합: ");

			if (isSpeed) printf("%s", GetTimeInHMS(newG + newH).c_str());
			else printf("%.3g % s", newG + newH, unitMessages[isSpeed].c_str());

			if (g[node] > newG) // 기존 누적 거리 > 현재 노드 누적 거리 + 다음 노드 거리면 갱신
			{
				g[node] = newG;
				prevs[node] = u;

				double fScore = newG + newH;
				q.emplace(fScore, node);
				printf(" O\n\n");
			}
			else
			{
				printf(" X\n\n");
			}
		}
		printf("-----------------------------\n");
	}

	int arrive = end;

	printf("역추적: %c ", arrive + 'A');
	arrive = prevs[arrive];

	while (arrive != -1)
	{
		printf("- %c ", arrive + 'A');
		arrive = prevs[arrive];
	}
	cout << endl;
	return g[end];
}

double Astar(diPair2D& graph, int start, int end, vector<double>& h)
{
	double2D speedMap = {};
	return Astar(graph, speedMap, start, end, h);
}

int main()
{
	vector<distAndCoord> roads = // 거리, u, v
	{
		{6.0, NODE::A, NODE::B},
		{3.0, NODE::A, NODE::C},
		{6.5, NODE::B, NODE::C},
		{7.0, NODE::B, NODE::D},
		{7.5, NODE::B, NODE::E},
		{2.0, NODE::C, NODE::D},
		{8.0, NODE::C, NODE::E},
		{3.0, NODE::D, NODE::F},
		{3.0, NODE::E, NODE::G},
		{2.0, NODE::F, NODE::G},
	};

	vector<double> h // G까지의 휴리스틱 경로
	{
		9.0, // A
		8.5, // B
		5.7,
		4.0,
		2.5,
		1.6,
		0.0
	};

	vector<distAndCoord> speeds // 각 지점 간 속도
	{
		{10.0, NODE::A, NODE::B},
		{15.0, NODE::B, NODE::A},

		{8.0, NODE::A, NODE::C},
		{8.0, NODE::C, NODE::A},

		{17.0, NODE::B, NODE::C},
		{22.0, NODE::C, NODE::B},

		{10.0, NODE::B, NODE::D},
		{12.0, NODE::D, NODE::B},

		{10.0, NODE::B, NODE::E},
		{15.0, NODE::E, NODE::B},

		{7.0, NODE::C, NODE::D},
		{7.0, NODE::D, NODE::C},

		{30.0, NODE::C, NODE::E},
		{25.0, NODE::E, NODE::C},

		{8.0, NODE::D, NODE::F},
		{15.0, NODE::F, NODE::D},

		{10.0, NODE::E, NODE::G},
		{9.0, NODE::G, NODE::E},

		{9.0, NODE::F, NODE::G},
		{14.0, NODE::G, NODE::F},
	};

	vector<distAndCoord> roads1 = // 거리, u, v
	{
		{6.0, NODE::A, NODE::B},
		{4.0, NODE::A, NODE::C},
		{5.0, NODE::B, NODE::C},
		{7.0, NODE::B, NODE::D},
		{6.0, NODE::B, NODE::E},
		{3.0, NODE::C, NODE::D},
		{8.0, NODE::C, NODE::E},
		{3.0, NODE::D, NODE::F},
		{3.0, NODE::E, NODE::G},
		{2.0, NODE::F, NODE::G},
	};

	vector<double> h1 // G까지의 휴리스틱 경로
	{
		9.0, // A
		6.5, // B
		7.0,
		4.0,
		2.5,
		1.0,
		0.0
	};

	diPair2D graph(SIZE);
	double2D speedMap = {};

	ConnectNode(roads, graph);
	SetSpeedMap(speedMap, speeds);

	cout << Dijkstra(graph, NODE::A, NODE::G) << "km" << endl << endl;
	cout << Astar(graph, NODE::A, NODE::G, h) << "km" << endl << endl;
	cout << GetTimeInHMS(Dijkstra(graph, speedMap, NODE::A, NODE::G, true)) << endl << endl;
	cout << GetTimeInHMS(Astar(graph, speedMap, NODE::A, NODE::G, h, true)) << endl << endl;
	return 0;
}