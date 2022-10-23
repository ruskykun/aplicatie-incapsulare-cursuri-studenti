#include "controller-professors.h"

struct View {
private:
	ControlEnrolment controlenrolment;
	ControlCourse controlcourse;
	Student student;
	
	void menu() {
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "\nBine ai venit, " << student.getFirstName() << " " << student.getLastName() << "!\n" << endl;
		cout << "Introduceti :" << endl;
		cout << "- 1 pentru a vedea toate cursurile disponibile" << endl;
		cout << "- 2 pentru a va inscrie la un curs" << endl;
		cout << "- 3 pentru a renunta la un curs" << endl;
		cout << "- 4 pentru a afisa cursurile la care sunteti inscris" << endl;
		cout << "- 5 pentru a vedea frecventa de elevi inscrisi la cursuri" << endl;
		cout << "- 6 pentru a sorta dupa numarul de participanti" << endl;
		cout << "- 7 pentru a va deloga" << endl;
	}

	void enrollCourse() {
		string numeCurs;
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "Introduceti numele cursului la care doriti sa va inscrieti :" << endl;
		cin >> numeCurs;
		int i = controlcourse.findByName(numeCurs);
		Course curs = controlcourse.getCourse(i);
		int idCurs = curs.getID();

		if (idCurs == -1) {
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "Acest curs nu exista!" << endl;
		}
		else if (controlenrolment.esteInscris(student.getID(), idCurs) == -1) {
			Enrolment x(controlenrolment.idUnic(), idCurs, student.getID());
			controlenrolment.addEnrolment(x);
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "Ati fost inscris la " << numeCurs << "!" << endl;
		}
		else {
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "Sunteti deja inscris la acest curs!" << endl;
		}
	}

	void removeEnrolment() {
		string numeCurs;
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "Introduceti numele cursului la care doriti sa renuntati :" << endl;
		cin >> numeCurs;
		int i = controlcourse.findByName(numeCurs);

		if (i == -1) {
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "Acest curs nu exista!" << endl;
		}
		else {
			Course curs = controlcourse.getCourse(i);
			int idCurs = curs.getID();
			int idEnrolment = controlenrolment.esteInscris(student.getID(), idCurs);
			if (idEnrolment != -1) {
				controlenrolment.removeEnrolment(idEnrolment);
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
				cout << "Ati renuntat la " << numeCurs << "!" << endl;
			}
			else {
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
				cout << "Nu sunteti inscris la acest curs!" << endl;
			}
		}
	}

	void afisareCursuriEnrolled() {
		int cursuri[100];
		int n;
		controlenrolment.cursuriEnrolled(cursuri, n, student.getID());
		controlcourse.afisareCursuriVector(cursuri, n);
		if (n == 0) {
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "Nu sunteti inscris la niciun curs!" << endl;
		}
	}

	void afisareFrecventaCursuri() {
		int frecventa[100]{};
		int n = controlcourse.getDim() - 1;
		controlenrolment.frecventaCursuri(frecventa, n);
		controlcourse.afisareCuFrecventa(frecventa, n);
	}

	void sortareDupaParticipanti() {
		int frecventa[100]{};
		int n = controlcourse.getDim() - 1;
		controlenrolment.frecventaCursuri(frecventa, n);
		controlcourse.sortareFrecventa(frecventa, n);
		controlcourse.afisareCuFrecventa(frecventa, n);
	}

	void logout(bool& running) {
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "V-ati delogat cu succes!" << endl;
		running = false;
	}

public:

	View(Student student) {
		this->student = student;
	}

	void play() {
		bool running = true;
		int p;

		while (running) {
			menu();
			string al;
			cin >> al;
			p = stoi(al);
			switch (p)
			{
			case 1:
				controlcourse.afisareCursuri();
				break;
			case 2:
				enrollCourse();
				break;
			case 3:
				removeEnrolment();
				break;
			case 4:
				afisareCursuriEnrolled();
				break;
			case 5:
				afisareFrecventaCursuri();
				break;
			case 6:
				sortareDupaParticipanti();
				break;
			case 7:
				logout(running);
				break;
			default:
				break;
			}
		}
	}
};