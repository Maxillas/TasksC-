//Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи.
//Напоминаю, что последовательность Фибоначчи определяется следующим образом:
//Fib(0)=0Fib(0)=0
//Fib(1)=1Fib(1)=1
//Fib(N)=Fib(N−1)+Fib(N−2)

template<int N>
struct Fib
{
    static int const value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0>
{
    static int const value = 0;
};

template<>
struct Fib<1>
{
    static int const value = 1;
};


//По аналогии со списком типов определите список целых чисел (int) времени компиляции IntList.
//Внутри списка должна быть константа Head, соответствующая числу в голове списка, и имя типа Tail, соответствующее хвосту списка.
//Пример:
//using primes = IntList<2,3,5,7,11,13>;
//constexpr int head = primes::Head;
//using odd_primes = primes::Tail;

template<int ... Types>
struct IntList;

template<int H, int ... T>
struct IntList<H, T...> {
    static const int Head = H;
    using Tail = IntList<T...>;
};

template<>
struct IntList<> {};

//Напишите метафункцию Length для вычисления длины списка IntList.
//Пример:
//using primes = IntList<2,3,5,7,11,13>;
//constexpr size_t len = Length<primes>::value; // 6

template<typename T>
struct Lenght
{
    static int const value = 1 + Lenght<typename T::Tail>::value;
};
