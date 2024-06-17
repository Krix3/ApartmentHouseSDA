#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

// ����� "�������"
class Person
{
private:
    char* name;

public:
    // �����������
    Person(const char* name)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // ����������� �����������
    Person(const Person& other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    // �������� ������������
    Person& operator=(const Person& other)
    {
        if (this != &other)
        {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        return *this;
    }

    // ����������
    ~Person()
    {
        delete[] name;
    }

    // ������� ������ ���������� � ��������
    void print() const
    {
        cout << "�������: " << name << endl;
    }
};

// ����� "��������"
class Apartment
{
private:
    Person** residents;
    size_t numResidents;

public:
    // �����������
    Apartment(size_t numResidents) : numResidents(numResidents)
    {
        residents = new Person * [numResidents];
    }

    // ������� ���������� ������
    void addResident(size_t index, const char* name)
    {
        if (index < numResidents)
        {
            residents[index] = new Person(name);
        }
    }

    // ����������� �����������
    Apartment(const Apartment& other) : numResidents(other.numResidents)
    {
        residents = new Person * [numResidents];
        for (size_t i = 0; i < numResidents; ++i)
        {
            residents[i] = new Person(*other.residents[i]);
        }
    }

    // �������� ������������
    Apartment& operator=(const Apartment& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < numResidents; ++i)
            {
                delete residents[i];
            }
            delete[] residents;

            numResidents = other.numResidents;
            residents = new Person * [numResidents];
            for (size_t i = 0; i < numResidents; ++i)
            {
                residents[i] = new Person(*other.residents[i]);
            }
        }
        return *this;
    }

    // ����������
    ~Apartment()
    {
        for (size_t i = 0; i < numResidents; ++i)
        {
            delete residents[i];
        }
        delete[] residents;
    }

    // ������� ������ ���������� � ��������
    void print() const
    {
        cout << "�������� � " << numResidents << " �������:" << endl;
        for (size_t i = 0; i < numResidents; ++i)
        {
            residents[i]->print();
        }
    }
};

// ����� "���"
class Building{
private:
    Apartment* apartments;
    size_t numApartments;

public:
    // �����������
    Building(size_t numApartments) : numApartments(numApartments)
    {
        apartments = new Apartment[numApartments];
    }

    // ������� ���������� ��������
    void addApartment(size_t index, size_t numResidents)
    {
        if (index < numApartments)
        {
            apartments[index] = Apartment(numResidents);
        }
    }

    // ������� ���������� ������ � ��������
    void addResidentToApartment(size_t apartmentIndex, size_t residentIndex, const char* name) {
        if (apartmentIndex < numApartments)
        {
            apartments[apartmentIndex].addResident(residentIndex, name);
        }
    }

    // ����������� �����������
    Building(const Building& other) : numApartments(other.numApartments)
    {
        apartments = new Apartment[numApartments];
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i] = other.apartments[i];
        }
    }

    // �������� ������������
    Building& operator=(const Building& other)
    {
        if (this != &other)
        {
            delete[] apartments;

            numApartments = other.numApartments;
            apartments = new Apartment[numApartments];
            for (size_t i = 0; i < numApartments; ++i)
            {
                apartments[i] = other.apartments[i];
            }
        }
        return *this;
    }

    // ����������
    ~Building()
    {
        delete[] apartments;
    }

    // ������� ������ ���������� � ����
    void print() const
    {
        cout << "������ � " << numApartments << " �������������:" << endl;
        for (size_t i = 0; i < numApartments; ++i)
        {
            apartments[i].print();
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // �������� ���� � 2 ����������
    Building building(2);

    // ���������� �������
    building.addApartment(0, 2);
    building.addApartment(1, 3);

    // ���������� ������� � ��������
    building.addResidentToApartment(0, 0, "���� ������");
    building.addResidentToApartment(0, 1, "����� �������");
    building.addResidentToApartment(1, 0, "���� ������");
    building.addResidentToApartment(1, 1, "���� �������");
    building.addResidentToApartment(1, 2, "������ �������");

    // ����� ���������� � ����
    building.print();

    return 0;
}