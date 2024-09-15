#include <iostream>

using namespace std;

template <typename T>
class CustomDeque
{
public:
    // 블록당 최대 크기
    static const size_t BLOCK_SIZE = 10;
    struct Block
    {
    private:
        std::vector<T> Data;

    public:
        Block() : Data() {}

        T& operator[](size_t index)
        {
            return Data[index];
        }

        void push_back(T input)
        {
            if (Data.size() < CustomDeque<T>::BLOCK_SIZE)
            {
                Data.push_back(input);
            }
        }

        void push_front(T input)
        {
            if (Data.size() < CustomDeque<T>::BLOCK_SIZE)
            {
                Data.insert(Data.begin(), input);
            }
        }

        void pop_front()
        {
            if (!Data.empty())
            {
                Data.erase(Data.begin());
            }
        }

        void pop_back()
        {
            if (!Data.empty())
            {
                Data.pop_back();
            }
        }

        size_t size() const
        {
            return Data.size();
        }

        bool empty() const
        {
            return Data.empty();
        }
    };

public:
    CustomDeque() : data() {}

    virtual ~CustomDeque()
    {
        data.clear();
    }

    void push_front(T input)
    {
        // 블록이 모두 주어진 사이즈만큼 꽉 차면 새로운 블록을 추가
        if (data.empty() || data.front()->size() == CustomDeque<T>::BLOCK_SIZE)
        {
            data.insert(data.begin(), std::make_unique<Block>());
        }
        // 첫번째 블록에 값 추가
        data.front()->push_front(input);
    }

    void push_back(T input)
    {
        // 블록이 모두 주어진 사이즈만큼 꽉 차면 새로운 블록을 추가
        if (data.empty() || data.back()->size() == CustomDeque<T>::BLOCK_SIZE)
        {
            data.push_back(std::make_unique<Block>());
        }
        // 마지막 블록에 값 추가
        data.back()->push_back(input);
    }

    void pop_front()
    {
        if (!data.empty())
        {
            data.front()->pop_front();
            if (data.front()->empty())
            {
                data.erase(data.begin());
            }
        }
    }

    void pop_back()
    {
        if (!data.empty())
        {
            data.back()->pop_back();
            if (data.back()->empty())
            {
                data.pop_back();
            }
        }
    }

    size_t size() const
    {
        // 각 블록 크기 더하기
        size_t total_size = 0;
        for (const auto& block : data)
        {
            total_size += block->size();
        }
        return total_size;
    }

    // 임의 접근을 위한 operator[] 연산자 오버로딩
    T& operator[](size_t index)
    {
        size_t block_index = index / BLOCK_SIZE;
        size_t element_index = index % BLOCK_SIZE;

        return (*data[block_index])[element_index];
    }

    bool empty() const { return data.empty(); }

private:
    std::vector<std::unique_ptr<Block>> data;
};

// 테스트
int main()
{
    CustomDeque<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_front(4);

    for (int i = 0;i<dq.size(); ++i)
    {
        cout << dq[i] << ' ';
    }

    return 0;
}
