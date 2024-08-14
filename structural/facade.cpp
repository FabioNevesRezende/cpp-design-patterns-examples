#include <iostream>
#include <memory>
#include <string>

using namespace std;

class DatabaseService
{
public:
    void storeReservation(const string& reservation)
    {
        cout << "Database: storing reservation: " << reservation << endl;
    }
};

class PaymentGateway
{
public:
    void processPayment(const string& paymentInfo)
    {
        cout << "Payment gateway: processing payment: " << paymentInfo << endl;
    }
};

class MessagingService
{
public:
    void sendConfirmation(const string& message)
    {
        cout << "Messaging service: sending confirmation message: " << message << endl;
    }
};

class ReservationSystemFacade
{
public:
    ReservationSystemFacade() : m_db(), m_paymentGateway(), m_messagingService() {}

    void makeReservation(const string& reservationInfo, const string& paymentInfo)
    {
        m_db.storeReservation(reservationInfo);
        m_paymentGateway.processPayment(paymentInfo);
        m_messagingService.sendConfirmation("Reservation confirmed");
    }

private:

    DatabaseService m_db;
    PaymentGateway m_paymentGateway;
    MessagingService m_messagingService;

};

int main(int argc, char* argv[])
{
    ReservationSystemFacade reservationSystem;
    const string reservation = "Room reservation 315";
    const string paymentInfo = "R$ 500,00";

    reservationSystem.makeReservation(reservation, paymentInfo);

    return 0;
}
