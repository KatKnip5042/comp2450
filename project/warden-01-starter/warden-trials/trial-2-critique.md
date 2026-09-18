# Trial II — *The Critique*

*Warden of the Foundations · Midterm 1 · 15 %*

This trial **requires** you to use an LLM. You will paste the prompt and the reply, then critique what you got. Reading and judging AI output is part of the job now; we are practicing it on purpose.

---

## The prompt

Open Claude (or your LLM of choice) and paste **this exact prompt**:

> *Write a C++ function template that returns the largest element of a `std::vector<T>`. Handle the case where the vector is empty. Briefly explain your design choices.*

Tell us which tool you used and the date:

- **Tool:** ChatGPT
- **Date of the conversation:** 2026-09-18

---

## The LLM's reply

Paste the **full reply**, code and prose. Use a fenced code block for the code. Do not edit the reply — we want to see what you actually got.

Write a C++ function template that returns the largest element of a std::vector<T>. Handle the case where the vector is empty. Briefly explain your design choices.

```cpp
#include <vector>
#include <stdexcept>

template <typename T>
T largest(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::invalid_argument("largest() called with an empty vector");
    }

    T max_value = values.front();

    for (const T& value : values) {
        if (value > max_value) {
            max_value = value;
        }
    }

    return max_value;
```

Design choices
const std::vector<T>& avoids copying the vector and prevents modification.

T is returned by value, which works naturally for typical value types such as int, double, and std::string.

The empty-vector case throws std::invalid_argument rather than returning an arbitrary value, since there is no largest element.

The comparison uses operator>, so T must support that operation.

Runtime complexity is O(n) with O(1) additional space.

---

## My critique  *( ≥ 150 words )*

Your critique must read like an engineer reviewing a colleague's pull request — specific, technical, and naming exactly what the LLM did. A vague critique ("looks fine to me, but it could be better") is *not* full credit even if the LLM's code was great.

Address each of these:

- **Compile.** Did you actually try to compile and run the code? On what types? What happened?
- **Empty case.** What does the empty-vector case actually do in this code? Is the LLM's choice reasonable? Is it different from what *you* would have chosen?
- **Requirements on `T`.** What does the code require of `T`? What happens if you instantiate it with a type that doesn't support `<` (e.g., a custom struct)?
- **Const-correctness.** Pass by value or by reference? Return by value or by reference? Would you change either?
- **`std::max_element`?** Did the LLM cheat by using the algorithm header, or did it write the loop? Which would *you* have shipped, and why?
- **One concrete improvement.** Name one specific change you would make before merging this into a real project. Not "make it better" — a concrete code change.

While this code does compile for multiple basic C++ types, we have to ensure that if implimenting a custom type to include required operators. Also, comparing strings would result in ones that have higher value rather than longest word. The empty vector case just checks that the vector is empty using .empty() and throws a invalid_argument. For this to work we would have to ensure we implement a try and catch block when running the code to actually catch the throw. As previously mentioned, T must support the operator>. It would crash without throwing an instance if you instantiate it with a type that doesn’t support <. The const is passed by reference which makes sense because you're not having to allocate memory to make a copy and it is not being modified because it is a const so there is no danger to this. ChatGPT did not use std::max_element. I did have to google but this would be the smarter option as it compares better than a manual loop would because there is more room for error with a manual loop than with max_element. Knowing that max_element is an option, I would pick max_element. The improvment I would make is including #include <algorithm> and replacing everything after the if statement with return *std::max_element(values.begin(), values.end()); There is of course a danger with this if using a unrecognized data type, so this would require a comparator.
