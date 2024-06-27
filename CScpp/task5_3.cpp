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
struct Length
{
    static int const value = 1 + Length<typename T::Tail>::value;
};

template<>
struct Length<IntList<>>
{
    static int const value = 0;
};

//Напишите две метафункции для работы c IntList:

//    IntCons позволяет увеличить список на один элемент — он добавляется в начало списка.
//    Generate позволяет сгенерировать список длины N с числами от 0 до N - 1.

//Пример:


//using L1 = IntList<2,3,4>;


//using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>

//using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>







//Напишите метафункцию Zip (аналог std::transform), которая принимает два списка целых чисел одинаковой длины, а так же бинарную метафункцию,
//и возвращает список, получившийся в результате поэлементного применения метафункции к соответствующим элементам исходных списков.

//Пример:

// бинарная метафункция
//template<int a, int b>
//struct Plus
//{
//    static int const value = a + b;
//};

// два списка одной длины
//using L1 = IntList<1,2,3,4,5>;
//using L2 = IntList<1,3,7,7,2>;

// результат применения — список с поэлементными суммами
//using L3 = Zip<L1, L2, Plus>::type;  // IntList<2, 5, 10, 11, 7>

// Шаблон для представления списка целых чисел
template<int... Ns>
struct IntList {};

// Пример бинарной метафункции Plus
template<int a, int b>
struct Plus {
    static constexpr int value = a + b;
};

// Основной шаблон для Zip
template<typename L1, typename L2, template<int, int> class F>
struct Zip;

// Частичная специализация для обработки непустых списков
template<int... Ns1, int... Ns2, template<int, int> class F>
struct Zip<IntList<Ns1...>, IntList<Ns2...>, F> {
    using type = IntList<F<Ns1, Ns2>::value...>;
};
