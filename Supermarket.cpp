#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm> 
using namespace std;
class Person {
protected:
    string name;
    string surname;
    string address;
    string Id;

public:
    Person(string name, string address) {
        this->name = name;
        this->address = address;

        // Génération de l'ID
        string c1 = name.substr(0, min<size_t>(3, name.size()));
        string c4 = address.substr(0, min<size_t>(3, address.size()));
            int c3 = rand() % 3000 + 1000;
        // Convertir en majuscules
        for (char& c : c1) c = toupper(c);
        for (char& c : c4) c = toupper(c);

        this->Id = "2024" + c1 + to_string(c3) + c4 ;
    }

    virtual string getId() {
        return this->Id;
    }

    virtual string getName() {
        return this->name;
    }

    virtual string getAddress() {
        return this->address;
    }


};

class Customer : public Person {
public:
    Customer(string name, string address)
        : Person(name, address) {}
};

class Supplier : public Person {
public:
    Supplier(string name,  string address)
        : Person(name, address) {}
};




class Product {
public:
    string Id;
    string name;
    int price;
    int quantity;
    string category;
    Supplier* supplier;

    Product(string name, int price, int quantity, string category, Supplier* sup = nullptr)
        : name(name), price(price), quantity(quantity), category(category), supplier(sup) {
        

        string c1 = supplier ? supplier->getId().substr(0, min<size_t>(3, name.size())) : "ISA";
        string c4 = name.substr(0, min<size_t>(2, name.size()));
        string c2 = category.substr(0, min<size_t>(1, category.size()));

        //to upper case
        for (char& c : c1) c = toupper(c);
        for (char& c : c2) c = toupper(c);
        for (char& c : c4) c = toupper(c);

        this->Id = "2024" + c1 + c4 + to_string(1002) + c2;
    }

    string getId() {
        return Id;
    }

    string getName() {
        return name;
    }

    string getCategory() {
        return category;
    }

    int getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    void updateProductPrice(int price) {
        this->price = price;
    }

    void updateProductQuantity(int quant) {
        this->quantity = quant;
    }

    void getProduct() {
        cout << "ID: " << Id
             << " Name: " << name
             << " Price: " << price
             << " Quantity: " << quantity
             << " Category: " << category;

        if (supplier) {
            cout << " Supplier: " << supplier->getName();
        } else {
            cout << " Supplier: None";
        }
        cout << endl;
    }

    string getSupplier() {
        return supplier ? supplier->getId() : "None";
    }
};

class Order{
private:
string Id;
string date;
Customer* customer;

public:
vector<Product*>productList;
 Order(string date,Customer* cust){
	this->customer=cust;
	this->date=date;
	string c1 = cust->getId().substr(0, min<size_t>(3, cust->getId().size()));
        string c2 = cust->getName().substr(1, min<size_t>(2, cust->getName().size()));
        string c4=date.substr(1, min<size_t>(3, date.size()));
        int c3 = rand() % 3000 + 1000;

        // to upper case
        for (char& c : c1) c = toupper(c);
        for (char& c : c2) c = toupper(c);

        this->Id = "2024" + c1 + to_string(c3)+c4 + c2;

}

void addProductOrder(Product* P){
	this->productList.push_back(P);
	cout<<"Adding of Product "<<P->getName()<<" sucessfully done"<<endl;
}
void displayOrder(){
	       cout << "ID: " << this->Id
             << " date: " << this->date
             << " Customer: " << this->customer->getName() << endl;	
	for(Product* product: this->productList){
		product->getProduct();
	}
}

int orderPrice(){
 int sum=0;
for(Product* product : this->productList){
	sum+=(product->getPrice())*(product->getQuantity());
}
	return sum;
}

string getId(){
	return this->Id;
}

};
class SupermarketStock{
private:
vector<Product*>productList;//a list of Order to facilitate the whole management of orders
vector<Order*>orderList;// a list of Product to facilitate the whole management of products

public:
SupermarketStock(){}

  //Adding a product in the inventory
 void createProduct(Product* P){
 	 Product* protest=nullptr;
  	for(Product* pro:productList){
  		if(pro->getName()==P->getName()){
		protest=pro;
		break;
  		}
  	}
  	if(protest==nullptr){
	productList.push_back(P);
	cout<<"Product "<<P->getId()<<" successfully added"<<endl;
	P->getProduct();
	}  
	else{
	cout<<"This product already exist in the stock.Please goto the Restock Option"<<endl;
	return;
	}	
  }
 
  
    //Check if a product is in stock
    
 int checkInventory(Product* P){
 	if(P->quantity>0){
 		return P->quantity;
 	}
 	else {
 
 		return 0;
 	}
 }
  
 Product* searchProduct(string id){
     if(productList.empty()){
    	cout<<"No product available"<<endl;
    }
 	Product* protest=nullptr;
	for(Product* product : productList){
		if(product->getId()==id){
			protest= product;
			break;
		}	
	
	} 
	return protest;
 }
  
 void restockProduct(string id,int quantity){ 
     if(productList.empty()){
    	cout<<"No product available"<<endl;
    }
 Product* product=searchProduct(id);
 
 if(product==nullptr){
 	cout<<"Missing Product in the stock"<<endl;
 	return;
 
 }else{
 	product->quantity+=quantity;
 	cout<<"Restocking of product "<<product->getName()<<" successfully done"<<endl;	
 }
 
 }
  
void processOrder(Product* P, int quantity) {
    P->quantity -= quantity;

    if (checkInventory(P) == 0) {
        productList.erase(remove(productList.begin(), productList.end(), P), productList.end());
    }
}

  //creating an order
   void createOrder(Order* ord){
   	int available=1;
   Product* stockproduct=nullptr;
   for(Product* ordpro : ord->productList){
	stockproduct=searchProduct(ordpro->getId());
   	 if(stockproduct==nullptr){
   		cout<<"Missing Product in the stock "<<ordpro->getName()<<endl;
   		available=0;
   	}
   	else if(ordpro->getQuantity()>stockproduct->getQuantity()){
   		cout<<"Insufficient stock for the product "<<ordpro->getName()<<endl;
   		available=0;
   	}
   }
   
   if(available){
           for (Product* ordpro : ord->productList) {
            for (Product* stockproduct : productList) {
                if (ordpro->getId()==stockproduct->getId()) {
                    	processOrder(stockproduct,ordpro->quantity);
                    	break;
                }
            }
            }
            orderList.push_back(ord);
            cout<<"Ordering successfully done"<<endl;
            ord->displayOrder();
            cout<<"Total Price : "<<ord->orderPrice()<<endl;
     }else{
     	cout<<"Order creation failed due to issue"<<endl;
     }
            
   }
   
   
   
   //seeking a product
   void searchProductByName(string name){
           if (productList.empty()) {
        cout << "No products available in stock." << endl;
        return; // Si vide, on sort de la fonction
   	 }
       Product* pro=nullptr;
    for(Product* product : productList){
    		if(product->getName()==name){
    			pro=product;
    			pro->getProduct();
    		}
    }
    if(pro==nullptr)
    	cout<<"Missing Product "<<pro->getSupplier()<<endl;
    }
   
   
   
   void searchProductByCategory(string category){
           if (productList.empty()) {
        cout << "No products available in stock." << endl;
        return; // Si vide, on sort de la fonction
   	 }
       Product* pro=nullptr;
       
    for(Product* product : productList){
    		if(product->getCategory()==category){
    			pro=product;
    			pro->getProduct();
    		}
    }
    if(pro==nullptr)
    	cout<<"No product for the category : "<<category<<endl;
    }
   
   
   
    void searchProductBySupplier(string id){
            if (productList.empty()) {
        cout << "No products available in stock." << endl;
        return; // Si vide, on sort de la fonction
   	 }
    Product* pro=nullptr;
    for(Product* product : productList){
    		if(product->getSupplier()==id){
    			pro=product;
    			pro->getProduct();
    		}
    }
    if(pro==nullptr)
    	cout<<"No product supplies by "<<pro->getSupplier()<<endl;
    }
    
    void updatePriceProduct(string id,int price){
            if (productList.empty()) {
        cout << "No products available in stock." << endl;
        return; // Si vide, on sort de la fonction
   	 }
     	Product* product=searchProduct(id);
 
	 if(product=nullptr){
	 	cout<<"Missing Product in the stock"<<endl;
	 
	 }else{
	 	product->updateProductPrice(price);
	 	cout<<"Updating of product"<<product->getName()<<"successfully done"<<endl;	
 	}    
    
    }
    //deleting a product
    void deleteProduct(string id){
        if(productList.empty()){
    	cout<<"No product available"<<endl;
    	return;
    }
     	Product* protest=nullptr;
     	
     	for(Product* product : productList){
		if(product->getId()==id){
			protest= product;
			break;
		}	
	
	} 
 
	 if(protest=nullptr){
	 	cout<<"Missing Product in the stock"<<endl;
	 
	 }else{
	 	cout<<"Deleting of product"<<protest->getName()<<"successfully done"<<endl;	
	 	productList.erase(remove(productList.begin(), productList.end(), protest), productList.end());
 	}	
    	
    }
    //cancelling an order
    void cancelOrder(string id){
        if(orderList.empty()){
    	cout<<"No order registred"<<endl;
      }
    	Order* ordertest=nullptr;
    	for(Order* order : orderList){
    		if(order->getId()==id){
    			ordertest=order;
    			break;
    		}
    	}
    if(ordertest==nullptr){
    	cout<<"Missing order"<<ordertest->getId()<<endl;
    }else{
    	cout<<"Cancelling of order"<<ordertest->getId()<<" successfully done"<<endl;
    	orderList.erase(remove(orderList.begin(), orderList.end(), ordertest), orderList.end());
    }
    }
    
    void displayProducts(){
        if (productList.empty()) {
        cout << "No products available in stock." << endl;
        return; // Si vide, on sort de la fonction
   	 }
      	for(Product* pro:productList){
                 pro->getProduct();
  		}
  	 }
  	 
  	 
    void displayOrders(){
    
    if(orderList.empty()){
    	cout<<"No order registred"<<endl;
    }
    else{
    	for(Order* order : orderList){
    		order->displayOrder();
    	}
    	
    }
   	}
};



int main(int argc, char* argv[]) {
    // Initialisation
    srand(time(0));
    SupermarketStock* Sp=new SupermarketStock();
    Supplier* supplier ;
    Customer* customer;
    Order* order;
    Product* product;
        //Useful variables
        int choix,indic=0,count=1;
        string id;
        string date1,date2,date;
        string name,name1,address,name2;
        string surname;
        string category;
        int price,c;
   	int i=0;
        int quantity;
        
                do{
            cout<<""<<endl;    
            cout<<"Welcome into the Stock Management System :)"<<endl;
            cout<<"Choose an unit : "<<endl;
            cout<<"1.Product management\n2.Order management\n0.Quit"<<endl;
            cin>>choix;
            switch(choix){
                case 1:
                    cout<<"1.Add a Product\n2.Delete a Product\n3.Find  a product by name\n4.Find a product by category\n5.Find a product by his supplier\n6.Display the list of product\n7.Restock a product\n8.Update a product(price)"<<endl;
                    cin>>choix;
                    switch(choix){
                        case 1:
                            cout<<"Insert the date (DD-MM-YY) :" ;
                            cin>>date;
                            cout<<"Supplier informations: "<<endl;
                            cout<<"Insert the supplier's name:";
                            cin>>name1;
                            cout<<"Address : ";
                            cin>>address;
                            supplier=new Supplier(name1,address);                              
                            do{                          	
                            cout<<"Insert the name of the product : ";
                            cin>>name;
                            cout<<"Insert the price of the product : ";
                            cin>>price;
                            cout<<"Insert the  quantity of the product : ";
                            cin>>quantity;
                            cout<<"Insert the category of the product : ";
                            cin>>category;
                           // product and supplier construction
                             product=new Product(name,price,quantity,category,supplier);
                             Sp->createProduct(product);
                             
		    	      cout<<"Do you want to add another product for this supplier ? (0 = continue, 1 = stop)"<<endl;
   			      cin>>indic;
		    	    }while(indic!=1);                             
                             cout<<"On: "<<date<<endl;
                             
                              
                             break;
                        case 2:
                        	cout<<"Insert the id of the product : ";
                        	cin>>id;
                        	Sp->deleteProduct(id);
                        	break; 
                        case 3:
                        	cout<<"Insert the name of the product : ";
				cin>>name2;
                        	Sp->searchProductByName(name2);
                        	break;
                        case 4:
                        	cout<<"Insert the category : ";
                        	cin>>category;
                        	Sp->searchProductByCategory(category);
                        	break;
                        case 5:
                        	cout<<"Insert the supplier id: ";
                        	cin>>name;
                        	Sp->searchProductBySupplier(name);
                        	break;
                        case 6:
                        	 cout<<"*********************List of products******************************"<<endl;
                        	Sp->displayProducts();
                        	break; 
                        case 7:
                        	cout<<"Insert the product ID : ";
                        	cin>>id;
                        	cout<<"Insert the quantity to add : ";
                        	cin>>quantity;
                        	Sp->restockProduct(id,quantity);
                        	break;
                        case 8:
                        	cout<<"Insert the product ID : ";
                        	cin>>id;
                        	cout<<"Insert the new price : ";
                        	cin>>price;  
                        	Sp->updatePriceProduct(id,price);   
                        	break;                  	
                        default:
                        	break; 	                                                 
                     }
                    break;
                case 2:
                cout<<"1.Create an order\n2.Cancel an order\n3.Display the list of order"<<endl;
            	cin>>choix; 
		    	 switch(choix){
		    	 case 1:
		    	  Product* prod[100];
                            cout<<"Insert the date (DD-MM-YY):";
                            cin>>date1;		    	    	
		    	     cout<<"Customer informations"<<endl;
		             cout<<"Insert the customer's name:";
		             cin>>name1;
		             cout<<"Address : "; 
		             cin>>address;
		             customer=new Customer(name1,address);                            	    		    	   	     order=new Order(date1,customer);	    		     
		    	     cout<<"Ordering product"<<endl;
		    	    do{
			    	cout<<"Insert the name of the product : ";
		               cin>>name;
		               cout<<"Insert the price of the product : ";
		               cin>>price;
		               cout<<"Insert the  quantity of the product : ";
				cin>>quantity;
		               cout<<"Insert the category of the product : ";
				cin>>category;   	                           
		               prod[i]=new Product(name,price,quantity,category);
				order->addProductOrder(prod[i]);
		    	 	i++;
		    	 	 cout<<"Do you want to add another product? (0 = continue, 1 = stop)"<<endl;
   				 cin>>indic;
		    	    }while(indic!=1);
		    	    //validation
		    	    Sp->createOrder(order);
		    	    break;
		    	 case 2:
		         cout<<"Insert the id of the order";
                        cin>>id;
                        Sp->cancelOrder(id);		       
		    	 break;
		    	 case 3:
		    	 cout<<"********************List of orders*****************************"<<endl;
		    	 Sp->displayOrders();
		    	 break;
		    	 
		    	 }               
                    break;
                case 0:
                   cout<<"Good bye!"<<endl;
                    break;
                default:
                	cout<<"Choix indisponible!"<<endl;
                    break;
            }
        }while(choix!=0);
   
    


    return 0;
}

