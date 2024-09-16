/*
@@ 커스텀 클래스 객체를 std::set에 저장하기 위해 operator< 연산자를 오버로딩한 예제
@@ operator<는 set의 정렬 기준을 정의하며, 우선순위(Priority)가 높을수록 먼저 오도록 정렬한다. 
@@ 만약 우선순위가 같다면, 작업(Task) 이름을 기준으로 정렬된다.
@@ 이를 통해 set은 GoodLifeProject 객체를 커스텀 정렬 방식으로 관리하게 됩니다.

*/
#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct GoodLifeProject 
{
    int Priority;
    string Task;

public:
    GoodLifeProject(int NewPriority, string NewTask) 
        : Priority(NewPriority) , Task(NewTask) {  }

// operator< 연산자 오버로딩
// 우선순위(Priority)가 높을수록 먼저 오도록 정렬
// 만약 우선순위가 같다면, 작업(Task) 이름을 기준으로 정렬된다.
    bool operator<(const GoodLifeProject& t) const 
    {
        if (Priority == t.Priority) 
        {
            return Task < t.Task;
        }
        return Priority > t.Priority;
    }
};

int main() 
{
    std::set<GoodLifeProject> tasks;

    tasks.insert(GoodLifeProject(1, "코딩테스트 한 문제"));
    tasks.insert(GoodLifeProject(0, "언리얼 프로젝트 개발하기"));
    tasks.insert(GoodLifeProject(2, "갓생프로젝트하기"));

    for (const auto& elem : tasks) 
    {
        std::cout << elem.Task << " " << '\n';
    }

    return 0;
}
