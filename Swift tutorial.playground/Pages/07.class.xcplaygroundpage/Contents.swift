//: [Previous](@previous)

//: ## Class

/*
class NewClassName: ParentClass {
    // Properties
    // Instance Methods
    // Type methods
}
*/

class BankAccount {
    var accountBalance: Float = 0
    var accountNumber: Int = 0
    
    let fee : Float = 25
    
    var balanceAfterFee : Float { //이런 식으로 getter setter를 만들어 쓸 수 있음...
        get {
            return accountBalance - fee
        }
        set( newBalance ) {
            accountBalance - fee
        }
    }
    
    init(number: Int, balance: Float) // initializer
    {
        accountNumber = number
        accountBalance = balance
    }
    
    init()
    {
        accountNumber = 0
        accountBalance = 0
    }
    deinit                          //deinitialize method
    {
        print("Deinitialize")
    }
    func displayBalance()
    {
        print("Number \(accountNumber)")
        print("Current balance is \(accountBalance)")
    }
    
    class func getMaxBalance() -> Float // class Method
    {
        return 100000.00
    }
}

var account1 = BankAccount(number: 12312312, balance: 400.54)
var account2 = BankAccount()
BankAccount.getMaxBalance()
account1.balanceAfterFee

//: [Next](@next)
