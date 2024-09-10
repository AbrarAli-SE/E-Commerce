#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

class Validations  //c;ass for input validations 
{
public:
    bool idValidation(string idString) 
    {
        for (int i = 0; i < idString.size(); ++i)
        {
            if (!isdigit(idString[i]))
            {
                return false;
            }
        }
        if (idString.empty())
        {
            return false;
        }
        for (int i = 0; i < idString.size(); ++i)
        {
            if (idString[i] == ' ')
            {
                return false;
            }
        }
        return true;
    }

    bool stringValidation(string str)
    {
        if (str.empty())
        {
            return false;
        }

        bool containSpacesOnly = false;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] != ' ')
            {
                containSpacesOnly = true;
                break;
            }
        }

        if (!containSpacesOnly)
        {
            return false;
        }

        return true;
    }
    bool adminStringValidation(string str)
    {
        if (str.empty())
        {
            return false;
        }
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == ' ')
            {
                return false;
                break;
            }
        }
        return true;
    }
};

class IDFile //class that used to id file handling
{
protected:
    vector<string> newIDs;
    vector<string> oldIDs;

public:
    void writeNewId(string id)
    {
        ofstream outfile("IDFile.txt", ios_base::app);
        outfile << id << "\n";
        outfile.close();
    }

    void readOldIdDetails()
    {
        ifstream infile("IDFile.txt");
        string idLine;
        while (getline(infile, idLine))
        {
            oldIDs.push_back(idLine);
        }
        infile.close();
    }
};
class IDFileHandling : protected IDFile, public Validations //class to managme ids
{
private:
    string productId;

public:
    bool idVerification(string idString)
    {
        readOldIdDetails();
        for (int i = 0; i < oldIDs.size(); ++i)
        {
            if (idString == oldIDs[i])
            {
                return false;
            }
        }
        return true;
    }

    int newProductIdStore() //to store new product id
    {
        while (true)
        {
            cout << "\n\tEnter Product Id :\t";
            getline(cin, productId);
            if (idValidation(productId))
            {
                if (idVerification(productId))
                {
                    newIDs.push_back(productId);
                    writeNewId(productId);
                    return stoi(productId);
                }
                else
                {
                    cout << "\n\tThis product id already exists!";
                }
            }
            else
            {
                cout << "\n\tInvalid Product Id!";
            }
        }
    }
};

class Product : public IDFileHandling // class to store products record
{
protected:
    string name;
    string description;
    double price;
    int id;
    bool available;

public:
    Product() {}
    Product(string name, string desc, double p, int i, bool avail = true) : name(name), description(desc), price(p), id(i), available(avail) {}

    string getName() const
    {
        return name;
    }

    string getDescription() const
    {
        return description;
    }

    double getPrice() const
    {
        return price;
    }

    int getId() const
    {
        return id;
    }

    bool isAvailable() const
    {
        return available;
    }

    void setAvailability(bool avail)
    {
        available = avail;
    }
};

class Pants //class to pent record 
{
protected:
    int pantCount;

public:
    Product pantProducts[50];
    Pants()
    {
        pantProducts[0] = Product("Gray Cotton Pant", "Size: Small, Color: Gray", 700, 1001);
        pantProducts[1] = Product("Black Denim Pant", "Size: Medium, Color: Black", 750, 1002);
        pantProducts[2] = Product("Blue Jeans Pant", "Size: Large, Color: Blue", 800, 1003);
        pantProducts[3] = Product("Beige Chino Pant", "Size: Small, Color: Beige", 720, 1004);
        pantProducts[4] = Product("Khaki Cargo Pant", "Size: Large, Color: Khaki", 780, 1005);
        pantCount = 5;
    }
    void userPantDisplay() const
    {
        cout << "\n\n\tGents Available Pants:";
        for (int i = 0; i < pantCount; i++)
        {
            cout << "\n\n\tName: " << pantProducts[i].getName();
            cout << "\n\tDescription: " << pantProducts[i].getDescription();
            cout << "\n\tPrice: " << pantProducts[i].getPrice();
            cout << "\n\tID: " << pantProducts[i].getId() << endl;
        }
    }
    void adminPantDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Pants:";
        for (int i = 0; i < pantCount; i++)
        {
            if (pantProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << pantProducts[i].getName();
                cout << "\n\tDescription: " << pantProducts[i].getDescription();
                cout << "\n\tPrice: " << pantProducts[i].getPrice();
                cout << "\n\tID: " << pantProducts[i].getId() << endl;
            }
        }
    }

    void addMultiplePants()
    {
        int numPantsToAdd;
        cout << "\n\tAvailable Pents in Store : " << pantCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many pants do you want to add more: ";
            getline(cin, stringNum);
            if (pantProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + pantCount) <= 50)
                {
                    numPantsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Pants can store only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numPantsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Pant " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (pantProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Pent Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (pantProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Pant Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (pantProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = pantProducts->newProductIdStore();
            if (pantCount < 50)
            {
                pantProducts[pantCount++] = Product(name, description, price, id);
                cout << "\n\tPant added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of pants reached!\n";
                break;
            }
        }
    }
};
class Shirts
{
protected:
    int shirtCount;

public:
    Product shirtProducts[50];

    Shirts()
    {
        shirtProducts[0] = Product("Gray Cotton T-Shirt", "Size: Small, Color: Gray", 700, 2001);
        shirtProducts[1] = Product("White Linen Shirt", "Size: Medium, Color: White", 750, 2002);
        shirtProducts[2] = Product("Blue Denim Shirt", "Size: Large, Color: Blue", 800, 2003);
        shirtProducts[3] = Product("Black Polo T-Shirt", "Size: Small, Color: Black", 720, 2004);
        shirtProducts[4] = Product("Red Checkered Shirt", "Size: Large, Color: Red", 780, 2005);
        shirtCount = 5;
    }

    void userShirtDisplay() const
    {
        cout << "\n\n\tGents Available Shirts:";
        for (int i = 0; i < shirtCount; i++)
        {
            if (shirtProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << shirtProducts[i].getName();
                cout << "\n\tDescription: " << shirtProducts[i].getDescription();
                cout << "\n\tPrice: " << shirtProducts[i].getPrice();
                cout << "\n\tID: " << shirtProducts[i].getId() << endl;
            }
        }
    }

    void adminShirtDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Shirts:";
        for (int i = 0; i < shirtCount; i++)
        {
            cout << "\n\n\tName: " << shirtProducts[i].getName();
            cout << "\n\tPrice: " << shirtProducts[i].getPrice();
            cout << "\n\tID: " << shirtProducts[i].getId();
            cout << "\n\tAvailability: " << (shirtProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleShirts()
    {
        int numShirtsToAdd;
        cout << "\n\tAvailable Shirts in Store : " << shirtCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many shirts do you want to add more: ";
            getline(cin, stringNum);
            if (shirtProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + shirtCount) <= 50)
                {
                    numShirtsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Shirts can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numShirtsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Shirt " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (shirtProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Shirt Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (shirtProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Shirt Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (shirtProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = shirtProducts->newProductIdStore();
            if (shirtCount < 50)
            {
                shirtProducts[shirtCount++] = Product(name, description, price, id);
                cout << "\n\tShirt added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of shirts reached!\n";
                break;
            }
        }
    }
};
class Suits
{
protected:
    int suitCount;

public:
    Product suitProducts[50];

    Suits()
    {
        suitProducts[0] = Product("Navy Blue 3-Piece Suit", "Includes Coat, Vest, Pants", 2000, 3001);
        suitProducts[1] = Product("Black Tuxedo Suit", "Includes Coat, Pants, Bowtie", 2500, 3002);
        suitProducts[2] = Product("Gray Slim Fit Suit", "Includes Coat, Pants", 1800, 3003);
        suitProducts[3] = Product("Brown Tweed Suit", "Includes Coat, Pants", 2200, 3004);
        suitProducts[4] = Product("Blue Pinstripe Suit", "Includes Coat, Pants", 1900, 3005);
        suitCount = 5;
    }

    void userSuitDisplay() const
    {
        cout << "\n\n\tGents Available Suits:";
        for (int i = 0; i < suitCount; i++)
        {
            if (suitProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << suitProducts[i].getName();
                cout << "\n\tDescription: " << suitProducts[i].getDescription();
                cout << "\n\tPrice: " << suitProducts[i].getPrice();
                cout << "\n\tID: " << suitProducts[i].getId() << endl;
            }
        }
    }

    void adminSuitDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Suits:";
        for (int i = 0; i < suitCount; i++)
        {
            cout << "\n\n\tName: " << suitProducts[i].getName();
            cout << "\n\tPrice: " << suitProducts[i].getPrice();
            cout << "\n\tID: " << suitProducts[i].getId();
            cout << "\n\tAvailability: " << (suitProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleSuits()
    {
        int numSuitsToAdd;
        cout << "\n\tAvailable Suits in Store : " << suitCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many suits do you want to add more: ";
            getline(cin, stringNum);
            if (suitProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + suitCount) <= 50)
                {
                    numSuitsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Suits can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numSuitsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Suit " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (suitProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Suit Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (suitProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Suit Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (suitProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = suitProducts->newProductIdStore();
            if (suitCount < 50)
            {
                suitProducts[suitCount++] = Product(name, description, price, id);
                cout << "\n\tSuit added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of suits reached!\n";
                break;
            }
        }
    }
};
class Frocks
{
protected:
    int frockCount;

public:
    Product frockProducts[50];

    Frocks()
    {
        frockProducts[0] = Product("Pink Floral Frock", "Size: Small, Color: Pink", 1200, 4001);
        frockProducts[1] = Product("Blue Party Frock", "Size: Medium, Color: Blue", 1500, 4002);
        frockProducts[2] = Product("Yellow Summer Frock", "Size: Large, Color: Yellow", 1100, 4003);
        frockProducts[3] = Product("White Lace Frock", "Size: Small, Color: White", 1300, 4004);
        frockProducts[4] = Product("Red Polka Dot Frock", "Size: Medium, Color: Red", 1400, 4005);
        frockCount = 5;
    }

    void userFrockDisplay() const
    {
        cout << "\n\n\tLadies Available Frocks:";
        for (int i = 0; i < frockCount; i++)
        {
            if (frockProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << frockProducts[i].getName();
                cout << "\n\tDescription: " << frockProducts[i].getDescription();
                cout << "\n\tPrice: " << frockProducts[i].getPrice();
                cout << "\n\tID: " << frockProducts[i].getId() << endl;
            }
        }
    }

    void adminFrockDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Frocks:";
        for (int i = 0; i < frockCount; i++)
        {
            cout << "\n\n\tName: " << frockProducts[i].getName();
            cout << "\n\tPrice: " << frockProducts[i].getPrice();
            cout << "\n\tID: " << frockProducts[i].getId();
            cout << "\n\tAvailability: " << (frockProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleFrocks()
    {
        int numFrocksToAdd;
        cout << "\n\tAvailable Frocks in Store : " << frockCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many frocks do you want to add more: ";
            getline(cin, stringNum);
            if (frockProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + frockCount) <= 50)
                {
                    numFrocksToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Frocks can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numFrocksToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Frock " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (frockProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Frock Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (frockProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Frock Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (frockProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = frockProducts->newProductIdStore();
            if (frockCount < 50)
            {
                frockProducts[frockCount++] = Product(name, description, price, id);
                cout << "\n\tFrock added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of frocks reached!\n";
                break;
            }
        }
    }
};
class Shoes
{
protected:
    int shoeCount;

public:
    Product shoeProducts[50];

    Shoes()
    {
        shoeProducts[0] = Product("Black Leather Heels", "Size: 7, Color: Black", 900, 5001);
        shoeProducts[1] = Product("White Sneakers", "Size: 8, Color: White", 800, 5002);
        shoeProducts[2] = Product("Red Ballet Flats", "Size: 6, Color: Red", 700, 5003);
        shoeProducts[3] = Product("Blue Wedge Sandals", "Size: 9, Color: Blue", 1000, 5004);
        shoeProducts[4] = Product("Pink Slippers", "Size: 7, Color: Pink", 600, 5005);
        shoeCount = 5;
    }

    void userShoeDisplay() const
    {
        cout << "\n\n\tLadies Available Shoes:";
        for (int i = 0; i < shoeCount; i++)
        {
            if (shoeProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << shoeProducts[i].getName();
                cout << "\n\tDescription: " << shoeProducts[i].getDescription();
                cout << "\n\tPrice: " << shoeProducts[i].getPrice();
                cout << "\n\tID: " << shoeProducts[i].getId() << endl;
            }
        }
    }

    void adminShoeDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Shoes:";
        for (int i = 0; i < shoeCount; i++)
        {
            cout << "\n\n\tName: " << shoeProducts[i].getName();
            cout << "\n\tPrice: " << shoeProducts[i].getPrice();
            cout << "\n\tID: " << shoeProducts[i].getId();
            cout << "\n\tAvailability: " << (shoeProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleShoes()
    {
        int numShoesToAdd;
        cout << "\n\tAvailable Shoes in Store : " << shoeCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many shoes do you want to add more: ";
            getline(cin, stringNum);
            if (shoeProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + shoeCount) <= 50)
                {
                    numShoesToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Shoes can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numShoesToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Shoe " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (shoeProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Shoe Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (shoeProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Shoe Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (shoeProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = shoeProducts->newProductIdStore();
            if (shoeCount < 50)
            {
                shoeProducts[shoeCount++] = Product(name, description, price, id);
                cout << "\n\tShoe added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of shoes reached!\n";
                break;
            }
        }
    }
};
class JewelrySet
{
protected:
    int jewelryCount;

public:
    Product jewelryProducts[50];

    JewelrySet()
    {
        jewelryProducts[0] = Product("Gold Necklace Set", "Includes Necklace, Earrings", 3000, 6001);
        jewelryProducts[1] = Product("Silver Bracelet Set", "Includes Bracelet, Ring", 2500, 6002);
        jewelryProducts[2] = Product("Pearl Earrings Set", "Includes Earrings, Hairpin", 2800, 6003);
        jewelryProducts[3] = Product("Diamond Pendant Set", "Includes Pendant, Chain", 3500, 6004);
        jewelryProducts[4] = Product("Ruby Bangle Set", "Includes Bangles, Anklet", 3200, 6005);
        jewelryCount = 5;
    }

    void userJewelryDisplay() const
    {
        cout << "\n\n\tLadies Available Jewelry Sets:";
        for (int i = 0; i < jewelryCount; i++)
        {
            if (jewelryProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << jewelryProducts[i].getName();
                cout << "\n\tDescription: " << jewelryProducts[i].getDescription();
                cout << "\n\tPrice: " << jewelryProducts[i].getPrice();
                cout << "\n\tID: " << jewelryProducts[i].getId() << endl;
            }
        }
    }

    void adminJewelryDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Jewelry Sets:";
        for (int i = 0; i < jewelryCount; i++)
        {
            cout << "\n\n\tName: " << jewelryProducts[i].getName();
            cout << "\n\tPrice: " << jewelryProducts[i].getPrice();
            cout << "\n\tID: " << jewelryProducts[i].getId();
            cout << "\n\tAvailability: " << (jewelryProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleJewelrySets()
    {
        int numJewelrySetsToAdd;
        cout << "\n\tAvailable Jewelry Sets in Store : " << jewelryCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many jewelry sets do you want to add more: ";
            getline(cin, stringNum);
            if (jewelryProducts->idValidation(stringNum))
            {
                if ((stoi(stringNum) + jewelryCount) <= 50)
                {
                    numJewelrySetsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Jewelry Sets can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numJewelrySetsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Jewelry Set " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (jewelryProducts->stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Jewelry Set Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (jewelryProducts->stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Jewelry Set Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (jewelryProducts->idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = jewelryProducts->newProductIdStore();
            if (jewelryCount < 50)
            {
                jewelryProducts[jewelryCount++] = Product(name, description, price, id);
                cout << "\n\tJewelry Set added successfully!\n";
            }
            else
            {
                cout << "\n\tMaximum number of Jewelry Sets reached!\n";
                break;
            }
        }
    }
};
class GentsProduct : public Pants, public Shirts, public Suits
{
public:
    void displayUserGentsShirts() const
    {
        userShirtDisplay();
    }

    void displayUserGentsPants() const
    {
        userPantDisplay();
    }

    void displayUserGentsSuits() const
    {
        userSuitDisplay();
    }

    void displayAdminGentsRecord() const
    {
        adminShirtDisplay();
        adminPantDisplay();
        adminSuitDisplay();
    }
};
class LadiesProduct : public Frocks, public Shoes, public JewelrySet
{
public:
    void displayUserLadiesFrocks() const
    {
        userFrockDisplay();
    }

    void displayUserLadiesShoes() const
    {
        userShoeDisplay();
    }

    void displayUserLadiesJewelrySets() const
    {
        userJewelryDisplay();
    }
    void displayAdminLadiesRecord() const
    {
        adminFrockDisplay();
        adminShoeDisplay();
        adminJewelryDisplay();
    }
};
class AllProducts : public GentsProduct, public LadiesProduct, public Validations
{
public:
    void allGentsProductDisplay() const
    {
        userPantDisplay();
        userShirtDisplay();
        userSuitDisplay();
    }
    void allLadiesProductDisplay() const
    {
        userFrockDisplay();
        userShoeDisplay();
        userJewelryDisplay();
    }
    void allProductsAdminRecord() const
    {
        displayAdminGentsRecord();
        displayAdminLadiesRecord();
    }
};

class AdminFile
{
protected:
    vector<string> oldUserNames;
    vector<string> oldPasswords;

public:
    void writeAdminDetails(string newUserName, string newPassword)
    {
        ofstream outfile("Admin File.txt", ios_base::app);
        outfile << newUserName << " " << newPassword << "\n";
        outfile.close();
    }

    void readAdminDetails()
    {
        ifstream infile("Admin File.txt");
        oldUserNames.clear();
        oldPasswords.clear();
        string adminRecordLine;
        while (getline(infile, adminRecordLine))
        {
            stringstream iss(adminRecordLine);
            string userName, password;
            iss >> userName >> password;
            oldUserNames.push_back(userName);
            oldPasswords.push_back(password);
        }
        infile.close();
    }
};
class AdminLogin : protected AdminFile, public Validations
{
private:
    string name;
    string password;

public:
    bool oldAdminLogin()
    {
        readAdminDetails();
        system("cls");
        while (true)
        {
            cout << "\n\tAdmin Login\n";
            while (true)
            {
                cout << "\n\tEnter Admin Username :\t";
                getline(cin, name);
                if (adminStringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid name!";
            }

            for (int i = 0; i < oldUserNames.size(); ++i)
            {
                if (name == oldUserNames[i])
                {
                    while (true)
                    {
                        cout << "\tEnter Admin Password :\t";
                        getline(cin, password);
                        if (adminStringValidation(password))
                        {
                            break;
                        }
                        cout << "\n\tInvalid Input!\n";
                    }
                    if (password == oldPasswords[i])
                    {
                        cout << "\n\tAdmin Log-In ";
                        for (int i = 0; i < 5; i++)
                        {
                            cout << ".";
                            Sleep(400);
                        }
                        cout << "\n\tLog-In Successful!";
                        return true;
                    }
                    else
                    {
                        cout << "\n\tInvalid Password!";
                        return false;
                    }
                }
            }
            cout << "\n\tAdmin Not Found!";
            return false;
        }
    }
    void newAdminRegistration()
    {
        system("cls");
        cout << "\n\tAdmin Registration\n";
        while (true)
        {
            cout << "\n\tEnter Admin Username :\t";
            getline(cin, name);
            if (adminStringValidation(name))
            {
                readAdminDetails();
                bool found = false;
                for (int i = 0; i < oldUserNames.size(); ++i)
                {
                    if (name == oldUserNames[i])
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    cout << "\n\tAdmin username already exists!";
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "\n\tInvalid User name!";
            }
        }
        while (true)
        {
            cout << "\tEnter Admin Password :\t";
            getline(cin,password);
            if(adminStringValidation(password))
            {
                break;
            }
            cout<<"\n\tInvalid Input!\n";
        }
        writeAdminDetails(name, password);
        cout << "\n\tRegisteration ";
        for (int i = 0; i < 5; i++)
        {
            cout << ".";
            Sleep(400);
        }
        cout << "\n\tRegistration Successful!";
    }
};

bool searchingLoop(string searchCriteria, AllProducts &allProducts);
bool deleteLoop(int productId, AllProducts &allProducts);

class CartBuyAndCheckOut : public Validations
{
protected:
    int cartItemsId;
    int soldItemsId;
    string customerName[50];
    double paidPayment[50];
    double totalPaidPayment;
    int quantityOfSoldsItems[50];

public:
    CartBuyAndCheckOut() : cartItemsId(0), soldItemsId(0), totalPaidPayment(0){};
    Product cartProduct[50];
    Product soldProduct[50];
    void addCart(int id, AllProducts &allProducts)
    {
        if (cartItemsId < 50)
        {
            for (int i = 0; i < 5; ++i)
            {
                if (allProducts.pantProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.pantProducts[i];
                    break;
                }
                else if (allProducts.shirtProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.shirtProducts[i];
                    break;
                }
                else if (allProducts.suitProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.suitProducts[i];
                    break;
                }
                else if (allProducts.frockProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.frockProducts[i];
                    break;
                }
                else if (allProducts.shoeProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.shoeProducts[i];
                    break;
                }
                else if (allProducts.jewelryProducts[i].getId() == id)
                {
                    cartProduct[cartItemsId] = allProducts.jewelryProducts[i];
                    break;
                }
            }
        }
        else
        {
            cout << "\n\tYour Product Cart limt is full";
        }
    }
    void showCart(AllProducts &allProducts)
    {
        if (cartItemsId == 0)
        {
            cout << "\n\tYour cart is empty." << endl;
        }
        else
        {
            system("cls");
            cout << "\n\tItems in your cart: " << cartItemsId;
            for (int i = 0; i < cartItemsId; ++i)
            {
                cout << "\n\n\tProduct ID: " << cartProduct[i].getId();
                cout << "\n\tProduct Name: " << cartProduct[i].getName();
                cout << "\n\tProduct Price: " << cartProduct[i].getPrice();
            }
        }
    }
    void clearCart()
    {
        cartItemsId = 0;
    }
    void clearPaymentRecord()
    {
        soldItemsId = 0;
        cout << "\n\tPayment Record cleared Successfull";
    }
    int getCartId()
    {
        return cartItemsId;
    }
    double calculateTotalBill()
    {
        double totalBill = 0.0;
        for (int i = 0; i < cartItemsId; ++i)
        {
            totalBill += cartProduct[i].getPrice();
        }
        return totalBill;
    }
    void payBill(double totalBill)
    {
        while (true)
        {
            cout << "\n\n\tTotal bill: " << totalBill << " Pkr";
            string stringAmount;
            while (true)
            {
                cout << "\n\tEnter the amount to pay: ";
                getline(cin, stringAmount);
                if (idValidation(stringAmount))
                {
                    break;
                }
                cout << "\n\tInvalid Amount!";
            }
            double amountPaid = stod(stringAmount);
            if (amountPaid >= totalBill)
            {
                double change = amountPaid - totalBill;
                while (true)
                {
                    cout << "\n\tPlease Enter Your Name : ";
                    getline(cin, customerName[soldItemsId]);
                    if (stringValidation(customerName[soldItemsId]))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Name!";
                }
                paidPayment[soldItemsId] = totalBill;
                totalPaidPayment += totalBill;
                quantityOfSoldsItems[soldItemsId] = cartItemsId;
                soldItemsId++;
                cout << "\n\tChange: " << change << " Pkr\n";
                cout << "\n\tHappy Shopping";
                clearCart();
                break;
            }
            else
            {
                cout << "\n\tInsufficient amount. Please pay the total bill amount.\n";
            }
        }
    }
    void buyProduct(AllProducts &allProducts)
    {
        string searchCriteria;
        while (true)
        {
            cout << "\n\tSearch a Product to buy (Name, Description, Id): ";
            getline(cin, searchCriteria);
            if (stringValidation(searchCriteria))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        bool found = false;
        found = searchingLoop(searchCriteria, allProducts);
        if (found)
        {
            string searchBuy;
            while (true)
            {
                cout << "\n\tEnter id of Product that you want to buy : ";
                getline(cin, searchBuy);
                if (idValidation(searchBuy))
                {
                    break;
                }
                cout << "\n\tInvalid ID!";
            }
            found = false;
            found = searchingLoop(searchBuy, allProducts);
            if (found)
            {
                system("cls");
                cout << "\n\tProduct Added Successfull in Cart";
                addCart(stoi(searchBuy), allProducts);
                cartItemsId++;
            }
        }
        if (!found)
        {
            cout << "\n\tNo matching product found.\n";
        }
    }
    void cartAndCheackOutProduct(AllProducts &allProducts)
    {
        string choice;
        while (true)
        {
            cout << "\n\n\t _________________________________________\n";
            cout << "\t|\t\tCart & Checkout   \t  |\n";
            cout << "\t|_________________________________________|\n";
            cout << "\t|   |" << setw(39) << "|\n";
            cout << "\t| 1 |  View Cart" << setw(28) << "|\n";
            cout << "\t| 2 |  Checkout" << setw(29) << "|\n";
            cout << "\t| 0 |  Back" << setw(33) << "|\n";
            cout << "\t|   |" << setw(39) << "|\n";
            cout << "\t|___|_____________________________________|\n";
            while (true)
            {
                cout << "\n\tEnter your choice: ";
                getline(cin, choice);
                if (idValidation(choice))
                {
                    break;
                }
                cout << "\n\tInvalid Input!";
            }
            if (choice == "1")
            {
                showCart(allProducts);
            }
            else if (choice == "2")
            {
                if (cartItemsId != 0)
                {
                    double totalBill = calculateTotalBill();
                    payBill(totalBill);
                }
                else
                {

                    cout << "\n\tYour cart is empty." << endl;
                }
            }
            else if (choice == "0")
            {
                break;
            }
            else
            {
                cout << "\n\tInvalid Choice!\n";
            }
        }
    }
    void checkPayment()
    {

        if (soldItemsId != 0)
        {
            system("cls");
            cout << "\n\tTotal Payments History: " << soldItemsId;
            for (int i = 0; i < soldItemsId; ++i)
            {
                cout << "\n\n\tCustomer Name: " << customerName[i];
                cout << "\n\tTotal Buy Product: " << quantityOfSoldsItems[i];
                cout << "\n\tPaid Bill: " << paidPayment[i];
            }
            cout << "\n\n\tTotal Received payment of sold Products :" << totalPaidPayment;
        }
        else
        {
            cout << "\n\tNo payment Record to Show";
        }
    }
    void paymentRecord()
    {
        string choice;
        while (true)
        {
            cout << "\n\n\t _________________________________________";
            cout << "\n\t|\tPayment Record Management   \t  |";
            cout << "\n\t|_________________________________________|";
            cout << "\n\t|   |" << setw(38) << "|";
            cout << "\n\t| 1 |  Check Payment Records" << setw(15) << "|";
            cout << "\n\t| 2 |  Clear Payment Records" << setw(15) << "|";
            cout << "\n\t| 0 |  Back" << setw(32) << "|";
            cout << "\n\t|___|_____________________________________|";
            while (true)
            {
                cout << "\n\tEnter your choice: ";
                getline(cin, choice);
                if (idValidation(choice))
                {
                    break;
                }
                cout << "\n\tInvalid Input!";
            }
            if (choice == "1")
            {
                system("cls");
                checkPayment();
            }
            else if (choice == "2")
            {
                system("cls");
                if (soldItemsId != 0)
                {
                    clearPaymentRecord();
                }
                else
                {
                    cout << "\n\tNo payment Record Found!";
                }
            }
            else if (choice == "0")
            {
                break;
            }
            else
            {
                cout << "\tInvalid choice. Please try again.\n";
            }
        }
    }
};

class Delete : public Validations
{
protected:
public:
    void deleteById(AllProducts &allProducts)
    {
        string deleteId;
        while (true)
        {
            cout << "\n\tEnter id of Product that you want to Delete : ";
            getline(cin, deleteId);
            if (idValidation(deleteId))
            {
                break;
            }
            cout << "\n\tInvalid ID!";
        }
        bool found = false;
        found = deleteLoop(stoi(deleteId), allProducts);
    }
    void searchAndDelete(AllProducts &allProducts)
    {
        string deleteCriteria;
        while (true)
        {
            cout << "\n\tSearch for delete Product by Name, Description or Id: ";
            getline(cin, deleteCriteria);
            if (stringValidation(deleteCriteria))
            {
                break;
            }
            cout << "\n\tInvalid Search!";
        }
        bool found = false;
        found = searchingLoop(deleteCriteria, allProducts);
        if (!found)
        {
            cout << "\n\tNo matching product found.\n";
        }
        else
        {
            deleteById(allProducts);
        }
    }
};

void storeName()
{
    system("cls");
    cout << "\t\n||||||      |||||| ||||||| ||\\\\    //|| ||\\\\    //|| ||||||| ||||||| |||||| ||||||";
    Sleep(120);
    cout << "\t\n||          ||     ||   || || \\\\  // || || \\\\  // || ||      ||   || ||     ||";
    Sleep(120);
    cout << "\t\n||||||  ||  ||     ||   || ||  \\\\//  || ||  \\\\//  || ||||||| ||||||| ||     ||||||";
    Sleep(120);
    cout << "\t\n||          ||     ||   || ||        || ||        || ||      ||  \\\\  ||     ||";
    Sleep(120);
    cout << "\t\n||||||      |||||| ||||||| ||        || ||        || ||||||| ||   \\\\ |||||| ||||||";
    Sleep(120);
}
string mainPage(AllProducts &allProducts)
{
    string choice;
    while (true)
    {
        cout << "\n\n\t _________________________________________\n";
        cout << "\t|\tE - COMMERCE Store   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Admin  " << setw(30) << "|\n";
        cout << "\t| 2 |  User   " << setw(30) << "|\n";
        cout << "\t| 0 |  Exit " << setw(32) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tPress a key to continue ... ";
            getline(cin, choice);
            if (allProducts.idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1" || choice == "2" || choice == "0")
        {
            return choice;
            break;
        }
        else
        {
            cout << "\n\tInvalid Choice!\n";
        }
    }
}
bool searchingLoop(string searchCriteria, AllProducts &allProducts)
{
    bool found = false;
    for (int i = 0; i < 50; ++i)
    {
        if (allProducts.pantProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.pantProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.pantProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.pantProducts[i].getName();
            cout << "\nDescription: " << allProducts.pantProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.pantProducts[i].getPrice();
            cout << "\nID: " << allProducts.pantProducts[i].getId() << endl;
        }
        if (allProducts.shirtProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.shirtProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.shirtProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.shirtProducts[i].getName();
            cout << "\nDescription: " << allProducts.shirtProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.shirtProducts[i].getPrice();
            cout << "\nID: " << allProducts.shirtProducts[i].getId() << endl;
        }
        if (allProducts.suitProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.suitProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.suitProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.suitProducts[i].getName();
            cout << "\nDescription: " << allProducts.suitProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.suitProducts[i].getPrice();
            cout << "\nID: " << allProducts.suitProducts[i].getId() << endl;
        }
        if (allProducts.frockProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.frockProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.frockProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.frockProducts[i].getName();
            cout << "\nDescription: " << allProducts.frockProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.frockProducts[i].getPrice();
            cout << "\nID: " << allProducts.frockProducts[i].getId() << endl;
        }
        if (allProducts.shoeProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.shoeProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.shoeProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.shoeProducts[i].getName();
            cout << "\nDescription: " << allProducts.shoeProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.shoeProducts[i].getPrice();
            cout << "\nID: " << allProducts.shoeProducts[i].getId() << endl;
        }
        if (allProducts.jewelryProducts[i].getName().find(searchCriteria) != string::npos ||
            allProducts.jewelryProducts[i].getDescription().find(searchCriteria) != string::npos ||
            to_string(allProducts.jewelryProducts[i].getId()).find(searchCriteria) != string::npos)
        {
            found = true;
            cout << "\nMatching Product Found:";
            cout << "\nName: " << allProducts.jewelryProducts[i].getName();
            cout << "\nDescription: " << allProducts.jewelryProducts[i].getDescription();
            cout << "\nPrice: " << allProducts.jewelryProducts[i].getPrice();
            cout << "\nID: " << allProducts.jewelryProducts[i].getId() << endl;
        }
    }
    return found;
}
bool deleteLoop(int productId, AllProducts &allProducts)
{
    bool found = false;
    for (int i = 0; i < 50; ++i)
    {
        if (allProducts.pantProducts[i].getId() == productId)
        {
            found = true;
            allProducts.pantProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.shirtProducts[i].getId() == productId)
        {
            found = true;
            allProducts.shirtProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.suitProducts[i].getId() == productId)
        {
            found = true;
            allProducts.suitProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.frockProducts[i].getId() == productId)
        {
            found = true;
            allProducts.frockProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.shoeProducts[i].getId() == productId)
        {
            found = true;
            allProducts.shoeProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.jewelryProducts[i].getId() == productId)
        {
            found = true;
            allProducts.jewelryProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tProduct with ID " << productId << " not found.\n";
    }

    return found;
}
void display(AllProducts &allProducts)
{
    string choice;
    while (true)
    {
        cout << "\n\n\t _________________________________________\n";
        cout << "\t|\tDisplay Product   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Gents Product" << setw(24) << "|\n";
        cout << "\t| 2 |  Ladies Product" << setw(23) << "|\n";
        cout << "\t| 3 |  Display All Products" << setw(17) << "|\n";
        cout << "\t| 0 |  Back" << setw(33) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (allProducts.idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1")
        {
            string gentsChoice;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\tDisplay Gents Product   \t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Pants" << setw(32) << "|\n";
                cout << "\t| 2 |  Shirts" << setw(31) << "|\n";
                cout << "\t| 3 |  Suits" << setw(32) << "|\n";
                cout << "\t| 4 |  All Products" << setw(25) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                while (true)
                {
                    cout << "\n\tEnter your choice: ";
                    getline(cin, gentsChoice);
                    if (allProducts.idValidation(gentsChoice))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Input!";
                }
                if (gentsChoice == "1")
                {
                    allProducts.displayUserGentsPants();
                }
                else if (gentsChoice == "2")
                {
                    allProducts.displayUserGentsSuits();
                }
                else if (gentsChoice == "3")
                {
                    allProducts.displayUserGentsSuits();
                }
                else if (gentsChoice == "4")
                {
                    allProducts.allGentsProductDisplay();
                }
                else if (gentsChoice == "0")
                {
                    break;
                }
                else
                {
                    cout << "\n\tInvalid Choice!\n";
                }
            }
        }
        else if (choice == "2")
        {
            string ladiesChoice;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\tDisplay Ladies Product   \t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Frocks" << setw(31) << "|\n";
                cout << "\t| 2 |  Shoes" << setw(32) << "|\n";
                cout << "\t| 3 |  Jewelry Sets" << setw(25) << "|\n";
                cout << "\t| 4 |  All Products" << setw(25) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                while (true)
                {
                    cout << "\n\tEnter your choice: ";
                    getline(cin, ladiesChoice);
                    if (allProducts.idValidation(ladiesChoice))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Input!";
                }
                if (ladiesChoice == "1")
                {
                    allProducts.displayUserLadiesFrocks();
                }
                else if (ladiesChoice == "2")
                {
                    allProducts.displayUserLadiesShoes();
                }
                else if (ladiesChoice == "3")
                {
                    allProducts.displayUserLadiesJewelrySets();
                }
                else if (ladiesChoice == "4")
                {
                    allProducts.allLadiesProductDisplay();
                }
                else if (ladiesChoice == "0")
                {
                    break;
                }
                else
                {
                    cout << "\n\tInvalid Choice!\n";
                }
            }
        }

        else if (choice == "3")
        {
            system("cls");
            allProducts.allGentsProductDisplay();
            allProducts.allLadiesProductDisplay();
        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            cout << "\n\tInvalid Choice!\n";
        }
    }
}
void searchProducts(AllProducts &allProducts)
{
    string searchCriteria;
    while (true)
    {
        cout << "\n\tSearch Any Product by Name, Description or Id: ";
        getline(cin, searchCriteria);
        if (allProducts.stringValidation(searchCriteria))
        {
            break;
        }
        cout << "\n\tInvalid Input!";
    }
    bool found = false;

    found = searchingLoop(searchCriteria, allProducts);
    if (!found)
    {
        cout << "\n\tNo matching product found.\n";
    }
}
void addProduct(AllProducts &allProducts)
{
    while (true)
    {
        string choice;
        cout << "\n\t _________________________________________\n";
        cout << "\t|\t\tAdd Product   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Pants" << setw(32) << "|\n";
        cout << "\t| 2 |  Shirts" << setw(31) << "|\n";
        cout << "\t| 3 |  Suits" << setw(32) << "|\n";
        cout << "\t| 4 |  Frocks" << setw(31) << "|\n";
        cout << "\t| 5 |  Shoes" << setw(32) << "|\n";
        cout << "\t| 6 |  Jewelry Sets" << setw(25) << "|\n";
        cout << "\t| 0 |  Back" << setw(33) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (allProducts.idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1")
        {
            system("cls");
            allProducts.addMultiplePants();
        }
        else if (choice == "2")
        {
            system("cls");
            allProducts.addMultipleShirts();
        }
        else if (choice == "3")
        {
            system("cls");
            allProducts.addMultipleSuits();
        }
        else if (choice == "4")
        {
            system("cls");
            allProducts.addMultipleFrocks();
        }
        else if (choice == "5")
        {
            system("cls");
            allProducts.addMultipleShoes();
        }
        else if (choice == "6")
        {
            system("cls");
            allProducts.addMultipleJewelrySets();
        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            cout << "\n\tInvalid category choice!\n";
        }
    }
}
void deleteProduct(Delete &deleteObject, AllProducts &allProducts)
{
    while (true)
    {
        cout << "\n\n\t _________________________________________";
        cout << "\n\t|\tDelete Product   \t\t  |";
        cout << "\n\t|_________________________________________|";
        cout << "\n\t|   |" << setw(38) << "|";
        cout << "\n\t| 1 |  Search and Delete " << setw(18) << "|";
        cout << "\n\t| 2 |  Delete by Product ID" << setw(16) << "|";
        cout << "\n\t| 0 |  Back" << setw(32) << "|";
        cout << "\n\t|___|_____________________________________|";
        string choice;
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (allProducts.idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }

        if (choice == "1")
        {
            deleteObject.searchAndDelete(allProducts);
        }
        else if (choice == "2")
        {
            deleteObject.deleteById(allProducts);
        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            cout << "\n\tInvalid choice!\n";
        }
    }
}

int main()
{
    AllProducts allProductsObject;
    AdminLogin adminLogin;
    CartBuyAndCheckOut cartBuyAndCheckOutObject;
    Delete deleteObject;
    storeName();
    while (true)
    {
        string choice = mainPage(allProductsObject);
        if (choice == "1")
        {
            bool adminVerification;
            adminVerification = adminLogin.oldAdminLogin();
            if (adminVerification == true)
            {
                string choice;
                while (true)
                {
                    cout << "\n\n\t _________________________________________\n";
                    cout << "\t|\t\tAdmin   \t\t  |\n";
                    cout << "\t|_________________________________________|\n";
                    cout << "\t|   |" << setw(39) << "|\n";
                    cout << "\t| 1 |  Available Products" << setw(19) << "|\n";
                    cout << "\t| 2 |  Add New Products" << setw(21) << "|\n";
                    cout << "\t| 3 |  Delete Products" << setw(22) << "|\n";
                    cout << "\t| 4 |  Payment Record" << setw(23) << "|\n";
                    cout << "\t| 5 |  Add Another Admin" << setw(20) << "|\n";
                    cout << "\t| 0 |  Log-Out" << setw(30) << "|\n";
                    cout << "\t|   |" << setw(39) << "|\n";
                    cout << "\t|___|_____________________________________|\n";
                    while (true)
                    {
                        cout << "\n\tPress a key to continue ... ";
                        getline(cin, choice);
                        if (allProductsObject.idValidation(choice))
                        {
                            break;
                        }
                        cout << "\n\tInvalid Input!";
                    }
                    if (choice == "1")
                    {
                        system("cls");
                        allProductsObject.allProductsAdminRecord();
                    }
                    else if (choice == "2")
                    {
                        system("cls");
                        addProduct(allProductsObject);
                    }
                    else if (choice == "3")
                    {
                        system("cls");
                        deleteProduct(deleteObject, allProductsObject);
                    }
                    else if (choice == "4")
                    {
                        system("cls");
                        cartBuyAndCheckOutObject.paymentRecord();
                    }
                    else if (choice == "5")
                    {
                        system("cls");
                        adminLogin.newAdminRegistration();
                    }
                    else if (choice == "0")
                    {
                        break;
                    }
                    else // wronge option
                    {
                        system("cls");
                        cout << "\n\tWronge Option!\n";
                    }
                }
            }
        }

        else if (choice == "2")
        {
            system("cls");
            string choice;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\t\tUser   \t\t\t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Display Products" << setw(21) << "|\n";
                cout << "\t| 2 |  Browse Products" << setw(22) << "|\n";
                cout << "\t| 3 |  Buy Product" << setw(26) << "|\n";
                cout << "\t| 4 |  Cart & Pay-Out" << setw(23) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                while (true)
                {
                    cout << "\n\tPress a key to continue ... ";
                    getline(cin, choice);
                    if (allProductsObject.idValidation(choice))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Input!";
                }
                if (choice == "1")
                {
                    display(allProductsObject);
                }
                else if (choice == "2")
                {
                    system("cls");
                    searchProducts(allProductsObject);
                }
                else if (choice == "3")
                {
                    system("cls");
                    cartBuyAndCheckOutObject.buyProduct(allProductsObject);
                }
                else if (choice == "4")
                {

                    system("cls");
                    cartBuyAndCheckOutObject.cartAndCheackOutProduct(allProductsObject);
                }
                else if (choice == "0")
                {
                    break;
                }
                else
                {
                    system("cls");
                    cout << "\n\tWronge Option!\n";
                }
            }
        }
        else if (choice == "0")
        {
            cout << "\n\n\t Thanks for using\n\t Good bye ... \n\n\n";
            break;
        }
    }
}