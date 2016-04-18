//: [Previous](@previous)

// 기본 class
class BankAccount {
    
    var accountBalance: Float
    var accountNumber: Int
    
    init(number: Int, balance: Float)
    {
        accountNumber = number
        accountBalance = balance
    }
    
    func displayBalance()
    {
        print("Number \(accountNumber)")
        print("Current balance is \(accountBalance)")
    }
}

class SavingsAccount: BankAccount { // 상속!!!
    var interestRate : Float = 0.0
    
    override init(number: Int, balance: Float) // 상속을 하여 initialize
    {
        interestRate = 0
        super.init(number: number, balance: balance)
    }
    init(number: Int, balance: Float, rate: Float) // 새로운 Initializer
    {
        interestRate = rate
        super.init(number: number, balance: balance)
    }
    
    func calculateInterest() -> Float
    {
        return interestRate * accountBalance
    }
    override func displayBalance() // overriding
    {
        super.displayBalance() //위에껄 먼저 부르고...
        print("Prevailing interest rate is \(interestRate)")
    }
}

var sBA = BankAccount(number: 1020, balance: 12700.00)
var sSA = SavingsAccount(number: 1022, balance: 12800.00)
var sSA2 = SavingsAccount(number: 1022, balance: 1229, rate: 2)

sBA.displayBalance()
sSA.displayBalance()
sSA2.displayBalance()
//: [Next](@next)
