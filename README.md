# Android scheme pattern resolver

**Combinatorics & Algorithms Design** assignment. The purpose of this assignment is to create an algorithm that computes all possible and legal Android scheme lock patterns.

## Lock Schemes

A pattern is legal iff:
- Each pattern must connect at least four dots.
- The dots in the pattern must all be distinct.
- If the line segment connecting any two consecutive dots in the pattern passes through any other dots, the other dots must have previously been in the pattern.

Android provides a 3*3 matrix by default.

## Instructions

This project uses `CMake 3.8` and newer

```
$ git clone https://github.com/HippoBaro/android_scheme_pattern.git
$ cd android_scheme_pattern && mkdir build && cd build
$ cmake ..
$ make
$ ./cellphone_cellphone_password
```

### CMake options

| Option           | Description                                                      | Default  |
| ---------------- | ---------------------------------------------------------------- |:--------:|
| `COMP_TIME_EVAL` | Computes the results at compile-time using `constexpr`.          |   OFF    |
| `PRINT_SCHEMES`  | Prints all found combinations on stdout.                         |   OFF    |
| `USE_SYMMETRY`   | Computes the results using symmetry (reduces computational cost) |   ON     |

## Implementation

The implementation consists of a directed graph traversed by a recursive algorithm that heuristically constructs all possible schemes.

### Compiler support

The code uses some C++17 features. It has been compiled successfully on:
- `GCC 7.1` and newer
- `Clang 3.9.0` and newer

If you don't have the required setup, here's a [Compiler Explorer link](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAKxAEZSBnVAV2OUxAHIBSAJgGY8AMwB2WIQGoAwtgAysgAoAJAPIA5bAH0FAQQDKegOoqASgBFt%2Bo6Yt7dMzUoULuABh19%2B4vCMzS5iqoalgbG5iHW4XY6Dk4u7m4eAj7IADbMWBLc/FLIDAT4IgTZ2ImeKemZ2VJCzASsmCVlySJpGX7VAG6YyETETQktbVU5IswAtpjEeMgDHoOCouL%2B8srqWrqhNhFhFmoqZlpxzV6YQj5%2BMqtBG1a7O9v7h47OZQsV7Vk5eQU%2Bxfyld6tSodHIAQ2IxDBAE85idhGIzitAusHuEAKoAFQAkrI9C94klTudfMi1sFNpELFjcfjjgl3kJllIVABZBS4rQ41labAANR0shO3lJKgUOPUgs0LLUekx2AAGgoTBI0CJ8pgAB4AB36C0wqQYjQWIr8YolailMrliuVJ0wYmEbyJHxGUghUNhAOdIjBkwY2rB7AkCDw2u1qAARhDUFkAOwAIWdEhTqtQ6oIWt1Ej%2BEjBkYYEFznTB6UwAEp40n3KnaznJBAS2WvlIJK5y4k612JMRMPViCIJE3mH4AFQSAC0tGy1Z03Z7fdYg%2BHjX4s9r3DjZmTqcz421qTBmeqBGh2odfr8mNIEgYeAAXphNAQJKkHXNaz5Uhc0xms8Q8zqWNzlSVIIHydAQBAD0YWqa9X3fAEsl4AA2PNIRhG9MSHUsR0rTd127IQSAkcCHyfF88C%2BMw2xnHMWwQkQ6L4JNeATPB8MTTt51TGDYQAVnY7h%2BJo7IaJXGduK7TdtxrVMZJ3FM9wPI9VykU9z19SYJHgu9H2fRiP1TL8fzVDUdQAsEgIkECwIgqC%2BLgm83yYpC%2BDQvib3skAxlA7UCGIZ9OMIrtiIAsj9Mo6jaLXejqkM2KWJYjiqyknjHMEvBhNE/gaN81J/P6Nc0o3Lc0oUhk513TB90PY8cg0i9tPg5h1TwYBfHQV902ABLASqlMzMzCzbwKByMK9KR4JcppUIkVBzyhPokty8CxugianL69yJAIUMbyG0bII2z0tpm705tQPbgpK1MwtIvSKLi3KYoTZ7W3Ot6krYjjbq7Pa8AAOiPIt8LYsT5r24GCFByS5K7Xt%2B0HAG4YG%2BNZPmNHlLqtTGq0q8b1au8OswLrUh67b4d/czs28xycmmxDsHmxajxIFiIEOunNoZ5ymZ2sEDvTfIjvG07ee2ubIxuqna258Wpr51zmYYCZorBVH51V8ZkKTF7I017tEaXW8JkNlMKsx2tsdUk8zyagnb3Igzzv6z8RG/Ukhv/QCiEY4A9rW476amiRRyVkpqeKOa%2BJltG5edqKIdcc263uiA6Ko%2BLPt15K4544yGwyoSROoiH8sKjtZYLiRI17MEAGtU9KjH52Ngcc1Ty3u/1R1JAAen7q4UQpO5thpPECWdcoliRYfyVuLYokxGIAGkp5NM4f3nm40VsFepHX%2BlMfKYFPmqen%2BsSfGAyDPxQ3DKMY1SqmbczFs8cvHSb1zPRyKMwah4GAMFGkGBuL80a6jwCWTMIA/qixOrBBmYcbx/0fJHTQ9NZxpW1MwSM35kBwMqvOb2I18hgIgJWEAEhMETUoRAmuIYwwRmjMQVAUFbIQFoZ6G8FcAodmKtXC2ZViHdlIdmToqA8BdVwQwBAEBsLjkOiufONd05WT9u5HaIgMB%2BGodwmEqjGEpmEKRHRIxtwvT4cQIxxjazmNBOJXCq4Qp2NTO3VyrjGGW28SI%2BO8k/HwPEZZay55MAN3oROSOiio4MJrqYiALkA7yPwrlZOVd/EFw8RIaxzcjaLg7jQ4uSTA6VgnBIacIk8nCIxkE4Ww1swaNjBGbUkTolh1iQReBtYmkLhfBDMJESBFeO7AYgSCYSkpMnBU7K0VcmCMyXWbJiNqno0UnWYJOYPY/l6ZM%2Bhh0ulCKWQUwcD8WExignssZwz4E90WZskypJem9iNDDWx84zlPzYRwvAoEuGeRycwPy/DVl3JIfUn2vS1QEDBD4QsijDowuIMAPslZDpRKQrmQ5izazp1zFQaKKdYoEvimglxuc2JUHefEhsYAwBjOEgmKg2UMluI2emAgPgRyrPnAk0c/zNqCWZSJVJliaKjiRSiggrK2XuJOaRP45Y9llIkMyhZvjW412yVOUFgSjmbN6WCEQ0JNCoCEEHDhrVeh4HTNUSMqBUBgQRfUgRzNdSkxmKpNF9TJyRyxVxI5uKSIRSeiSl6RK3phtbGS5i4NKXUoLgkhlQrZlaLmu6/AyBVICtOimkVMrZV9JNkWIo5ZEkOmSZE1VNzA0BM1Vk%2BVOr1XdjBWIiFI0YkHMuqzZaglsohoMiIb1GYqzZOTQmJiVTip%2BJbqjO5ngHT4AHkPAIC896aDlGvDemMb6BmDJ81h7CQCBmAQAdxIOgTQ7A/IIHTB0ANVtqq1VtjkXMUhHUTHVD/IoEgTCoFPQwABqogEgJPQwc9xBL0OIgTgvBBCiGPq7PkYgzBegSEDHtTQ0HsWMLAxBqDujqjvvSOML9v7/2AaQuOBxPLUzyyQVIe1jqbzEc/SA8cf6AOR06HgO8mZ0BztrYNdt2YswEMIOho8CAsO6IgHhi9MmsBEY/aRhgN5OOUeZqOQ6DiqE5Nk7pm8PG%2BOk3oThtxB6LkgE4cZwgpMbxCFLEaGtOK63rPBX%2BEaTHUgsymGzIqYrOY%2Bow9J7DqFiAIAYMOkW5m7HZOw2kl6EWGCAxo82guraC6bO875paJA6ViSCyOkLimOjhci9F/pD62XZLpRAZLZcXoStDFF2jNTbllQWfA5gd4RC9QcZochyBwEQ0s98kAQ2m45BKw4ljKn1QdI000LrRz6OTXk5B0rymSNkaWwCObO32Pka41R/TWBKMjJTN5QMeAipSD%2BN%2B/4zM0AXp8KpC76zcH4JmAhupnnswbYI1geh1CHGFmseWIWr3fSZkLDdPV9yRMhL9lKzQfwpiaAjH8QsgOts5FY6p9TFHI7aZ9ZK1FsSMUq3WiHXHaWpAE928TqjB22NNGqzXNb1Q6eEfx/NtTx3NMoOkPzyOiNopdM65dusY2j2cMRrwoFBUQUrdcymXpkY%2BynswA6QlbWbLBt6WmtC0HqGjjBwmniCT3IJbFbtFr8YpCblbDb3RjWaLk%2Bld0mu0KuUuPczXXp6BNTIDmbowGL3INvdh4Dc4xARblIBgwKnkfCjvdj7d/I%2BuenWXQNCUP5dw%2Bp%2Bj5gFLRo1RdUTy1lPDqo8w9L4Dcv6YBOq7ZUHzUPmIae5r9D9PceE/294z3uvffM//Gl/OIP0JO8vW7yUYv9ey89Gb9MpPw%2B08x6b2IQTau6xQrYcA6KwfQ/jjzz58peeT8SGD6kHfbKEnIAPyAsS6S4mFoSbLhyBYIA39SaUF6n%2B0E3%2BZ%2B5Ylu9%2BDYN%2BXwzMrgXwAAYt7oWmvvPrXhvg3v3v0jkIXlgBHigSXilugchChFokJrKg4jgb3jHgQdUF3hCFKuvngRnvHi%2BAhoWgXHPgCAvqPkwS2FgZgOQSPpQWPoQcQbvmymQZwYIdwdQbPtXsgRQWgWPgWqwQjH2IyprgQNru%2BHGkmKXBDK7kpulrKjJBIAaEaG/sofWKRGflAW2HAQgbKkgRwbgYvo3svmIDwVYkXs4enlvl1MbvYWIV4fIUvhXh4R7rQX2PQS4b4RICwRYf9BEQQFET4W4X4ZgZ4dgRIQ3jEf4SQYEZkd4ZvqkWEYPsnnIQIdkakUofESmCsoJOoZoUxNoami9Pof7nkS2gjmyj4jXD0Ymg2IAXsojH/hUtUVqvKisoYW3BMaoVMW5qIl2AatZFmiIJoFQBMNqM%2BKgBAANpNoQSFo9rtIkZVuYbyg2Enu7oQRAObroq1oJJ7iygEXKkjDZE5u0YhulNZOjsQAoFIkUM/i9Kjt8Zjn8QQIWO5NcRboyg8SKnfjSqRIMRWoHN8b8djiMe2KcWoobtZMbg0TroONQiiaCVFpiXYgknSniQ6GMYWr7mMO8coTNm7gQPuBAJSUOtnt2AkiFjgUULCuqBnKhMydqKKhDFONSbKtko5oaPSW4n0TxHKfOIyZkEKQKShJCbcR2PcYkY8XMSoS8dydCnyeCYKfuCKS9FOMIXNHStyYMpQlTrZvxtCdqVOtLpluyv9sjrGCsWsRsTsbooNjCsNvsVJicbFjxHij%2BlnOGpnAxIzkdntl9NoSlGGYwg/kaj6fuFsXJlJj/KAU8XqSbFlLqXWAqfki8U2q6V0W2h6b7LGAFGCN0PHpgH6VgAGWAoQZJtdL6khFzjkMwH8ChAACzPis6qaLbM7Mwpndi9lSD9lFBDkjki6HbjknZupSYMAuQS5cRS72G5hRk0QRoB5dhKl%2BAnkQBJ4ua4ZSaAyyLyLuQnmXk1ynqhhvikTZlQzKqxn84rkknG4KrRTenrEskhagE2Fimkk8Q2k65DL2m8Z2YCaZQtEe4oYyl2IhYbm64rQ0TqnnaaklxmCAz1mNlGjvkICPkZYzo1zoUzSCTcnKo6pVLNGt5Pkvl%2BCkU3kLR2klDQYFYyG8bkU8TZLUWISVm1JUwKRdYI4Lp9wSCDw7yoiUj3CKWPAHBHCvCVS7p3xMKPyHpQS47XoFS3qkhhlvxqRvr86HF7ZuyphpBgiH6463zBhhlQIwIcDwIzk84GEM4WWC4lCjkLYcYTk0Jg5wkphfbwZ/Y0wAQOV7rNl6alZw4wYkGGoFh67FlBrhS5gF7RmxTZWthxmxqsQJjIBgFETBq5gATJx0SVU5C%2BWJTaE2JJWiGjIhWCT5iAYiT8GoH4FCEQxFQT41wJWMrtXZRdUME5EvSzDpWDWtUJgjWdVg4S6oRDXMWFrfRzUFgcntYkGlnbUfG1jmjYiSiyDSjqA2hKgqjPKl6OrdBtI9k048yzkDnDkED%2BXxlBXYozzMhsgciyBcjYg8iaD8iCj2EzlzkEALmvVLlsY/mRzCWDh6HbmWIDUpjqI4moRtGxHBUakQUfLMJfJHqTZ2yaRfyeVqRxlE6rl6VSalZvWw1IQhZbWdmRablYVnZ8FEVTAkUgX67dwCCmHGi75g3PWLlxn01rl7QYUI2tFI367eTdC9Dsw5DeStR4AACOI4mOAU1Q3ke09cLe/%2BzMetmAYI6AH2JBaNmiGNqEpu2NuFuN3YxtptKWNUKk7Amg0Yw2FqIA4wjcT4qtGtakutCA%2BtJQGcfaNtuiN49565NFokHOhagBRNDU9s%2BMkmZ6Cm9OFNdV2A1NmGs20NY5gVq5zNTNtY8NucGRHNUIxFzZPN010kW4eZDdayFtJAEARu1tKETtXU1CPdv5CdxiPdVOVAfxlCvNO5vcS69hQlsdIlHW9aayklYlRIi6piclq6u8yl4Q29tg9galhI8IZ8boyAfwjUmmzopl1Q5lh2llE5iQvSUCRQmgLyQKby5hPWPgvUgB%2BlBohld61NGdm2jl7xaUh1x1p1so8oF1tZ6GqAwCeAkYvyhAeApe0UMVd822bGlNmmlCgMLyN1cVoVEg4NkNu0V0aVriEZScL0/AMZ8UYtxdF2FK7EluT9BA5qfAvAfA/EXUi1aA4wSDMONq6o1CPDXDEgyo2IzAQ5yE3D/EUgTRvAP8LE9AcDCDSD34nKpejKWUsJxZRA/S4ML0EYGjyD2jHV%2BFXclFYV0wRQnDvAvAmIV0pYYjvA/EEjUjMjg5cjwkijXDN4hjAl2Sio2ImIG66IDO2ABgc6k9mMuYvtPgZmg9QldjBAL9peb91QyjEg3DAI49y9nAkOqQXA/EnApAIgXArg5T7CnATu2ht4LAbAZW/AtA5TBAVTRTkODcIA/A/AgMfTgzQzwzKEpAJTnAg55TlTnA1TpAtT5TDAIArgpAHTMzRTpAcAsASAAj2ovyUw5AlAOzezxAIAwAcYyjIEmY8elAkYnTpAQjEI0IXAbTpAAjkwRQKgHsTzazpAWAvtfWb4dz%2BAvY1q3QizPzWoPQdQHAnALz6O4zszAUeA4wnTxTiDizkAkOC0nKwsXAk4EEYksw2htAcYk4Kg/Ak4hgUwbCAEE4hgpY5%2BVLmo9Zk4ZgLI7InImg3IvIAoQouULzTArA7AdAxTpTUzdztTmoAAHChBOLI8AMgKHnGIDLwKRLgIQCRJ4Go%2B%2BvuMc8hK0%2BWO06i9070/08M%2Ba4M6M%2BM5MxUxK1wAs0sys6ixszAIgCACwAQLgq9RQEFrq2%2BCc/QB6n0CK2M2K7az87U1qxIKeoQAgBINK7K/K4qxIMq7wEa2s6AaQD030wMxa%2Ba6GxM%2BKxG/a4wI66s9U5m%2BM2m%2BG7M/M06xm5DsRSIyAIOUAA%3D)

## Performances

The code is tuned for performance with the exclusive use of fixed-sized arrays (no dynamic allocation).

## Bonus

### Arbitrary-sized matrix

The algorithm is not limited by a 3 * 3 matrix but is able to work with arbitrary-sized matrices by using `password_space<Collumns, Rows>`.

### Fully compile-time evaluated

I took this opportunity to play with C++ **`constexpr`** keyword and compile-time evaluation. The algorithm is fully compliant with constexpr limits.
As a result, for a specified matrix of 2 by 2, the produced assembly is as follows (compiled with `GCC 7.2`) :

```asm
.LC0:
  .string "%d nodes combinations: %lu\n"
.LC1:
  .string "Total: %lu\n"
main:
  sub rsp, 8
  mov edx, 24
  mov esi, 4
  mov edi, OFFSET FLAT:.LC0
  xor eax, eax
  call printf
  mov esi, 24
  mov edi, OFFSET FLAT:.LC1
  xor eax, eax
  call printf
  xor eax, eax
  add rsp, 8
  ret
```
The produced assembly directly incorporates the result of the computation (24 schemes of 4 nodes possibles).

### Multithreaded Pure functional

The recursive algorithm implements only pure functions, and thus is completely stateless.
When compile-time evaluation in not enabled, the program takes advantage of this and shard the workload across multiple threads.

### Symmetry resolve

Using symmetry, the algorithm reduces the computational cost of resolving all schemes by 85% in a best-case scenario.