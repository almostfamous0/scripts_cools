fn fac_rec(n: u128) -> u128 {
    match n {
        0 => 1,
        1 => 1,
        _ => fac_rec(n-1) * n,
    }
}

fn factorial(n: u128) -> u128 {
    let mut sum: u128 = 1;
    
    for x in 2..n+1 {
        sum *= x;
    }
    sum
}

fn main() {
 println!("{}", fac_rec(30));
 println!("{}", factorial(30));
 ()
}
