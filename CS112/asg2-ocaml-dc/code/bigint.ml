(* $Id: bigint.ml,v 1.5 2014-11-11 15:06:24-08 - - $ *)

open Printf

module Bigint = struct

    type sign     = Pos | Neg
    type bigint   = Bigint of sign * int list
    let  radix    = 10
    let  radixlen =  1

    let car       = List.hd
    let cdr       = List.tl
    let map       = List.map
    let reverse   = List.rev
    let append    = List.append
    let strcat    = String.concat
    let strlen    = String.length
    let strsub    = String.sub
    let zero      = Bigint (Pos, [])

    let charlist_of_string str = 
        let last = strlen str - 1
        in  let rec charlist pos result =
            if pos < 0
            then result
            else charlist (pos - 1) (str.[pos] :: result)
        in  charlist last []

    let bigint_of_string str =
        let len = strlen str
        in  let to_intlist first =
                let substr = strsub str first (len - first) in
                let digit char = int_of_char char - int_of_char '0' in
                map digit (reverse (charlist_of_string substr))
            in  if   len = 0
                then zero
                else if   str.[0] = '_'
                     then Bigint (Neg, to_intlist 1)
                     else Bigint (Pos, to_intlist 0)

    let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))


    let rec cmp list1 list2 = match (list1, list2) with
        | [], []    ->  0
        | list1, [] ->  1
        | [], list2 -> -1
        | car1::cdr1, car2::cdr2 -> 
            let comp = cmp cdr1 cdr2 
            in if(comp = 0 && car1 > car2) then 1
            else if(comp = 0 && car1 < car2) then -1
            else if(comp = 0 && car1 = car2) then 0
            else if (comp = 1)then 1
            else -1

    let rec rmZero' list1 = match (list1) with
        | [] -> [0]
        | car1::cdr1 -> 
            if(car1 = 0)
            then rmZero' cdr1
            else car1::cdr1

    let rmZero list1 =
        let revlist = reverse list1 
        in reverse (rmZero' revlist)


    let rec add' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1
        | [], list2, 0       -> list2
        | list1, [], carry   -> add' list1 [carry] 0
        | [], list2, carry   -> add' [carry] list2 0
        | car1::cdr1, car2::cdr2, carry ->
          let sum = car1 + car2 + carry
          in  sum mod radix :: add' cdr1 cdr2 (sum / radix)


    let rec sub' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0      -> list1
        | list1, [], carry  -> sub' list1 [carry] 0
        | [], list2, 0      -> []
        | [], list2, carry  -> []
        | car1::cdr1, car2::cdr2, carry ->
            let diff = car1 - car2 - carry
            in if (diff >= 0 || cdr1 == [])
                then diff :: sub' cdr1 cdr2 0 
                else diff + radix :: sub' cdr1 cdr2 1

    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if (neg1 = neg2 )
        then Bigint (neg1, add' value1 value2 0)
        else if(cmp value1 value2 = 1) 
        then Bigint(neg1, rmZero (sub' value1 value2 0))
        else Bigint(neg2, rmZero (sub' value2 value1 0))

    let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        if (neg1 = neg2 && cmp value1 value2 = -1 && neg1 = Pos)
            then Bigint (Neg,  rmZero (sub' value2 value1 0))
        else if(neg1 = neg2 && cmp value1 value2 = -1 && neg1 = Neg)
            then Bigint (Pos,  rmZero (sub' value2 value1 0))
        else if(neg1 != neg2)
            then Bigint (neg1, rmZero (add' value1 value2 0))
        else Bigint (neg1, rmZero (sub' value1 value2 0))

    let rec mul' list1 list2 carry = match(list1, list2, carry) with
        | [], list2, 0 -> []
        | [], list2, carry -> [carry]
        | list1, [], 0 -> []
        | list1, [], carry -> [carry]
        | car1::cdr1, car2::cdr2, carry ->
            if(car1 = 0) then 0 :: mul' cdr1 list2 0 
            else
                let product = car1 * car2 + carry in
                add' (product mod radix :: 
                        mul' [car1] cdr2 (product / radix))
                     (mul' (append [0] cdr1) list2 0) 0


    let mul (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        if (neg1 = neg2 && cmp value1 value2 != 1)
            then Bigint (Pos, mul' value1 value2 0)
        else if(neg1 = neg2 && cmp value1 value2 = 1) 
            then Bigint (Pos, mul' value2 value1 0)
        else if(neg1 != neg2 && cmp value1 value2 != 1)
            then Bigint (Neg, mul' value1 value2 0)
        else Bigint (Neg, mul' value2 value1 0)

    let rec convertToInt list1 n = match(list1, n) with
        | [], n -> 0
        | car1::cdr1, n ->
            (car1 * n) + convertToInt cdr1 (n * 10)


    let rec div' list1 list2 carry = match(list1, list2, carry) with
        | [], list2, 0 -> []
        | [], list2, carry -> [carry]
        | list1, [], 0 -> []
        | list1, [], carry -> [carry]
        | car1::cdr1, car2::cdr2, carry ->
            if(car1 = 0) then 0 :: div' cdr1 list2 0 
            else
                let quotient = (car2 / (convertToInt list1 1))
                 + carry in
                add' (quotient mod radix :: 
                        div' [convertToInt list1 1] cdr2 
                        (quotient / radix))
                     (div' (append [0] cdr1) list2 0) 0


    let div (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        Bigint (Pos, rmZero (div' value2 value1 0)) 

    let rem = add

    let rec pow' list1 list2 = match(list1, list2) with 
        | [], list2 -> list2
        | list1, [] -> []
        | list1, list2->
            if(cmp list1 [1] = 0) then list2
            else mul' list2 (pow' (sub' list1 [1] 0) list2) 0

    let pow (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
    if(neg1 = Neg) then zero
    else Bigint (Pos, pow' value1 value2)
end

