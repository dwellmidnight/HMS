
#include <stdio.h>
#include <conio.h>
#include <string.h>


//----------------------------------------USER - HMS--------------------------------------------------
// Define a structure to represent users
struct User {
    char username[50];
    char password[50];
    int role; // 1 for admin, 2 for doctor, 3 for nurse, etc.
};



// Function to validate user login
int validateLogin(struct User users[], int numUsers, char username[], char password[]) {
    int i;
    for (i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return users[i].role;
        }
    }
    return -1; // Invalid login
}




//------------------------------------------- FOR - PATIENT - START ------------------------------------------------
// ---------------------------Structures to store information-------------------------------
struct Patient {
    char name[100];
    int age;
    char address[100];
    char phone[15];
    double bloodPressure;
    double temperature;
};


// -----------------------------------------Forward declaration-------------------------------------------
void displayPatients();
void searchPatients();
void deletePatient();


//------------------------------------------- Function to add a patient--------------------------------------------

void addPatient(struct Patient patients[], int *patientCount) {
    struct Patient newPatient;

    // Check if there is space in the patients array
    if (*patientCount >= 100) {
        printf("Patient limit reached. Cannot add more patients.\n");
        return;
    }

    // Clear the input buffer
    while (getchar() != '\n');

    // Input patient details
    printf("Enter patient name: ");
    fgets(newPatient.name, sizeof(newPatient.name), stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = '\0'; // Remove the newline character

    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    while (getchar() != '\n'); // Consume the newline character and any additional characters

    printf("Enter patient address: ");
    fgets(newPatient.address, sizeof(newPatient.address), stdin);
    newPatient.address[strcspn(newPatient.address, "\n")] = '\0'; // Remove the newline character

    printf("Enter patient phone number: ");
    fgets(newPatient.phone, sizeof(newPatient.phone), stdin);
    newPatient.phone[strcspn(newPatient.phone, "\n")] = '\0'; // Remove the newline character

    // Input blood pressure and temperature
    printf("Enter blood pressure: ");
    scanf("%lf", &newPatient.bloodPressure);
    
    printf("Enter temperature: ");
    scanf("%lf", &newPatient.temperature);

    // Add the new patient to the patients array
    patients[*patientCount] = newPatient;
    (*patientCount)++;

    printf("Patient added successfully!\n");
}

// -------------------------------------------------- Update patient -----------------------------------------------
// Function to update a patient's record
void updatePatient(struct Patient patients[], int patientCount) {
    char searchName[100]; // Maximum name length assumed to be 100 characters
    int foundIndex = -1,i; // Initialize foundIndex to -1 (not found)
    int choice;

    if (patientCount == 0) {
        printf("No patients available for update.\n");
        return;
    }

    // Ask the user for the patient's name to search for
    printf("Enter the name of the patient you want to update: ");
    scanf("%s", searchName);

    // Iterate through the patients array to find the matching patient
    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            foundIndex = i;
            break; // Exit the loop when a match is found
        }
    }

    if (foundIndex != -1) {
        // Found a matching patient, now update it
        printf("Updating patient: %s\n");

        // Ask the user what they want to update
        
        do {
            printf("Select the field to update:\n");
            printf("1. Name\n");
            printf("2. Age\n");
            printf("3. Address\n");
            printf("4. Phone Number\n");
            printf("5. Done (Exit)\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    // Update the patient's name
                    printf("Enter updated patient name: ");
                    while (getchar() != '\n');
                    fgets(patients[foundIndex].name, sizeof(patients[foundIndex].name), stdin);
                    patients[foundIndex].name[strcspn(patients[foundIndex].name, "\n")] = '\0'; // Remove the newline character
                    break;
                case 2:
                    // Update the patient's age
                    printf("Enter updated patient age: ");
                    scanf("%d", &patients[foundIndex].age);
                    while (getchar() != '\n'); // Consume the newline character and any additional characters
                    break;
                case 3:
                    // Update the patient's address
                    printf("Enter updated patient address: ");
                    while (getchar() != '\n');
                    fgets(patients[foundIndex].address, sizeof(patients[foundIndex].address), stdin);
                    patients[foundIndex].address[strcspn(patients[foundIndex].address, "\n")] = '\0'; // Remove the newline character
                    break;
                case 4:
                    // Update the patient's phone number
                    printf("Enter updated patient phone number: ");
                    while (getchar() != '\n');
                    fgets(patients[foundIndex].phone, sizeof(patients[foundIndex].phone), stdin);
                    patients[foundIndex].phone[strcspn(patients[foundIndex].phone, "\n")] = '\0'; // Remove the newline character
                    break;
                case 5:
                    // Exit the update loop
                    printf("Patient record updated successfully!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 5);
    } else {
        printf("No matching patient found for update.\n");
    }
}


// ---------------------------------------------  Function to delete patient data ---------------------------------

void deletePatient(struct Patient patients[], int *patientCount) {
    int i;
    char searchName[100]; // Maximum name length assumed to be 100 characters
    int foundIndex = -1; // Initialize foundIndex to -1 (not found)

    if (*patientCount == 0) {
        printf("No patients available for deletion.\n");
        return;
    }

    // Ask the user for the patient's name to search for
    printf("Enter the name of the patient you want to delete: ");
    scanf("%s", searchName);

    // Iterate through the patients array to find the matching patient
    for (i = 0; i < *patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            foundIndex = i;
            break; // Exit the loop when a match is found
        }
    }

    if (foundIndex != -1) {
        // Found a matching patient, now delete it
        for (i = foundIndex; i < (*patientCount - 1); i++) {
            // Shift elements to fill the gap left by the deleted patient
            patients[i] = patients[i + 1];
        }
        (*patientCount)--;
        printf("Patient '%s' has been deleted.\n");
    } else {
        printf("No matching patient found for deletion.\n");
    }
}


// ------------------------------- function to display Patient data ---------------------------------

void displayPatients(struct Patient patients[], int patientCount) {
    int i;
    if (patientCount == 0) {
        printf("No patients available for display.\n");
        return;
    }

    printf("Patients:\n");
    for (i = 0; i < patientCount; i++) {
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Address: %s\n", patients[i].address);
        printf("Phone: %s\n", patients[i].phone);
        printf("Blood Pressure: %lf\n", patients[i].bloodPressure); // Include blood pressure
        printf("Temperature: %lf\n", patients[i].temperature);     // Include temperature
        printf("\n");
    }
}



//--------------------------------------------function to search patient data ----------------------------

void searchPatients(struct Patient patients[], int patientCount) {
    char searchName[100]; // Maximum name length assumed to be 100 characters
    int found = 0; // Flag to indicate if a match is found
    int i;

    if (patientCount == 0) {
        printf("No patients available for search.\n");
        return;
    }

    // Ask the user for the patient's name to search for
    printf("Enter the name of the patient you want to search for: ");
    scanf("%s", searchName);

    printf("Search results:\n");
    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            // Found a matching patient, print their details
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Address: %s\n", patients[i].address);
            printf("Phone: %s\n", patients[i].phone);
            printf("Blood Pressure: %lf\n", patients[i].bloodPressure); // Include blood pressure
            printf("Temperature: %lf\n", patients[i].temperature);     // Include temperature
            printf("\n");
            found = 1; // Set the found flag to 1
        }
    }

    if (!found) {
        printf("No matching patient found.\n");
    }
}



// -------------------------------------------------- END --------------------------------------------------



// ------------------------------------------ FOR - DOCTOR - START --------------------------------------------------

// ---------------------------Structures to store information-------------------------------
struct Doctor {
    char name[100];
    char address[100];
    char phone[15];
    char specialization[100];
    int experience; // Add doctor experience
    char joinDate[20]; // Add join date
};


// -----------------------------------------Forward declaration-------------------------------------------

void deleteDoctor();
void displayDoctors();
void searchDoctors();


// -------------------------------------Function to add a doctor-----------------------------------------

void addDoctor(struct Doctor doctors[], int *doctorCount) {
    struct Doctor newDoctor;
    // Check if there is space in the doctors array
    if (*doctorCount >= 100) {
        printf("Doctor limit reached. Cannot add more doctors.\n");
        return;
    }

    // Input doctor details
    printf("Enter doctor name: ");
    scanf("%s", newDoctor.name);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter doctor address: ");
    scanf("%s", newDoctor.address);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter doctor phone number: ");
    scanf("%s", newDoctor.phone);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter doctor specialization: ");
    scanf("%s", newDoctor.specialization);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter doctor experience (in years): ");
    scanf("%d", &newDoctor.experience);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter doctor join date (YYYY-MM-DD): ");
    scanf("%s", newDoctor.joinDate);
    while (getchar() != '\n');  // Clear the input buffer

    // Add the new doctor to the doctors array
    doctors[*doctorCount] = newDoctor;
    (*doctorCount)++;

    printf("Doctor added successfully!\n");
}

// ---------------------------------------------------------------------- UPDATE RECORD
// Function to update a doctor's record
void updateDoctor(struct Doctor doctors[], int doctorCount) {
    int choice;
    char searchName[100]; // Maximum name length assumed to be 100 characters
    int foundIndex = -1,i; // Initialize foundIndex to -1 (not found)

    if (doctorCount == 0) {
        printf("No doctors available for update.\n");
        return;
    }

    // Ask the user for the doctor's name to search for
    printf("Enter the name of the doctor you want to update: ");
    scanf("%s", searchName);

    // Iterate through the doctors array to find the matching doctor
    for (i = 0; i < doctorCount; i++) {
        if (strcmp(doctors[i].name, searchName) == 0) {
            foundIndex = i;
            break; // Exit the loop when a match is found
        }
    }

    if (foundIndex != -1) {
        // Found a matching doctor, now update it
        printf("Updating doctor: %s\n");

        // Ask the user what they want to update
        
        do {
            printf("Select the field to update:\n");
            printf("1. Name\n");
            printf("2. Address\n");
            printf("3. Phone Number\n");
            printf("4. Specialization\n");
            printf("5. Experience\n");
            printf("6. Join Date\n");
            printf("7. Done (Exit)\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    // Update the doctor's name
                    printf("Enter updated doctor name: ");
                    while (getchar() != '\n');
                    fgets(doctors[foundIndex].name, sizeof(doctors[foundIndex].name), stdin);
                    doctors[foundIndex].name[strcspn(doctors[foundIndex].name, "\n")] = '\0'; // Remove the newline character
                    break;
                case 2:
                    // Update the doctor's address
                    printf("Enter updated doctor address: ");
                    while (getchar() != '\n');
                    fgets(doctors[foundIndex].address, sizeof(doctors[foundIndex].address), stdin);
                    doctors[foundIndex].address[strcspn(doctors[foundIndex].address, "\n")] = '\0'; // Remove the newline character
                    break;
                case 3:
                    // Update the doctor's phone number
                    printf("Enter updated doctor phone number: ");
                    while (getchar() != '\n');
                    fgets(doctors[foundIndex].phone, sizeof(doctors[foundIndex].phone), stdin);
                    doctors[foundIndex].phone[strcspn(doctors[foundIndex].phone, "\n")] = '\0'; // Remove the newline character
                    break;
                case 4:
                    // Update the doctor's specialization
                    printf("Enter updated doctor specialization: ");
                    while (getchar() != '\n');
                    fgets(doctors[foundIndex].specialization, sizeof(doctors[foundIndex].specialization), stdin);
                    doctors[foundIndex].specialization[strcspn(doctors[foundIndex].specialization, "\n")] = '\0'; // Remove the newline character
                    break;
                case 5:
                    // Update the doctor's experience
                    printf("Enter updated doctor experience (in years): ");
                    scanf("%d", &doctors[foundIndex].experience);
                    while (getchar() != '\n'); // Consume the newline character and any additional characters
                    break;
                case 6:
                    // Update the doctor's join date
                    printf("Enter updated doctor join date (YYYY-MM-DD): ");
                    while (getchar() != '\n');
                    fgets(doctors[foundIndex].joinDate, sizeof(doctors[foundIndex].joinDate), stdin);
                    doctors[foundIndex].joinDate[strcspn(doctors[foundIndex].joinDate, "\n")] = '\0'; // Remove the newline character
                    break;
                case 7:
                    // Exit the update loop
                    printf("Doctor record updated successfully!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 7);
    } else {
        printf("No matching doctor found for update.\n");
    }
}



// ------------------------------------------ FUNCTION TO DELETE DOCTOR RECORD ------------------------
void deleteDoctor(struct Doctor doctors[], int *doctorCount) {
    int foundIndex = -1; // Initialize foundIndex to -1 (not found)
    int i;
    char searchName[100]; // Maximum name length assumed to be 100 characters

    if (*doctorCount == 0) {
	printf("No doctors available for deletion.\n");
	return;
    }

    // Ask the user for the doctor's name to search for
    printf("Enter the name of the doctor you want to delete: ");
    scanf("%s", searchName);



    // Iterate through the doctors array to find the matching doctor
    for (i = 0; i < *doctorCount; i++) {
	if (strcmp(doctors[i].name, searchName) == 0) {
	    foundIndex = i;
	    break; // Exit the loop when a match is found
	}
    }

    if (foundIndex != -1) {
	// Found a matching doctor, now delete it
	for (i = foundIndex; i < (*doctorCount - 1); i++) {
	    // Shift elements to fill the gap left by the deleted doctor
	    doctors[i] = doctors[i + 1];
	}
	(*doctorCount)--;
	printf("Doctor '%s' has been deleted.\n", searchName);
    } else {
	printf("No matching doctor found for deletion.\n");
    }
}


// --------------------------------- FUNCTION TO SEARCH DOCTOR DATA -------------------------

void searchDoctors(struct Doctor doctors[], int doctorCount) {
    char searchName[100]; // Maximum name length assumed to be 100 characters
    int found = 0; // Flag to indicate if a match is found
    int i;

    if (doctorCount == 0) {
	printf("No doctors available for search.\n");
	return;
    }

    // Ask the user for the doctor's name to search for
    printf("Enter the name of the doctor you want to search for: ");
    scanf("%s", searchName);

    printf("Search results:\n");
    for (i = 0; i < doctorCount; i++) {
	if (strcmp(doctors[i].name, searchName) == 0) {
	    // Found a matching doctor, print their details
	    printf("Name: %s\n", doctors[i].name);
	    printf("Address: %s\n", doctors[i].address);
	    printf("Phone: %s\n", doctors[i].phone);
	    printf("Specialization: %s\n", doctors[i].specialization);
	    printf("\n");
	    found = 1; // Set the found flag to 1
	}
    }

    if (!found) {
	printf("No matching doctor found.\n");
    }
}


// ---------------------------------- FUNCTION TO DISPLAY DOCTOR RECORD ---------------------------------

void displayDoctors(struct Doctor doctors[], int doctorCount) {
    int i;
    if (doctorCount == 0) {
        printf("No doctors available for display.\n");
        return;
    }

    printf("Doctors:\n");
    for (i = 0; i < doctorCount; i++) {
        printf("Name: %s\n", doctors[i].name);
        printf("Address: %s\n", doctors[i].address);
        printf("Phone: %s\n", doctors[i].phone);
        printf("Specialization: %s\n", doctors[i].specialization);
        printf("Experience: %d years\n", doctors[i].experience);
        printf("Join Date: %s\n", doctors[i].joinDate);
        printf("\n");
    }
}


// ------------------------------------------ END ---------------------------------------------------------------------



// ---------------------------------------- FOR APPOINTMENT START -------------------------------------


// ---------------------------Structures to store information------------------------------
struct Appointment {
    struct Patient patient;
    struct Doctor doctor;
    char date[20];
    char time[10];
};



// ---------------------------------------------------- FORWARD DECLARATION -------------------------------
void deleteAppointment();
void displayAppointments();
void searchAppointments();


// ----------------------------------Function to book an appointment------------------------------------------

void bookAppointment(struct Appointment appointments[], int *appointmentCount) {
    struct Appointment newAppointment;

    // Check if there is space in the appointments array
    if (*appointmentCount >= 100) {
        printf("Appointment limit reached. Cannot book more appointments.\n");
        return;
    }

    // Input patient information
    printf("Enter patient name: ");
    scanf("%s", newAppointment.patient.name);
    while (getchar() != '\n'); // Consume the newline character and any additional characters

    printf("Enter patient address: ");
    scanf("%s", newAppointment.patient.address);
    while (getchar() != '\n');

    printf("Enter patient phone number: ");
    scanf("%s", newAppointment.patient.phone);
    while (getchar() != '\n');

    // Input doctor information
    printf("Enter doctor name: ");
    scanf("%s", newAppointment.doctor.name);
    while (getchar() != '\n');

    printf("Enter doctor address: ");
    scanf("%s", newAppointment.doctor.address);
    while (getchar() != '\n');

    printf("Enter doctor phone number: ");
    scanf("%s", newAppointment.doctor.phone);
    while (getchar() != '\n');

    printf("Enter doctor specialization: ");
    scanf("%s", newAppointment.doctor.specialization);
    while (getchar() != '\n');

    // Input date and time
    printf("Enter appointment date (YYYY-MM-DD): ");
    scanf("%s", newAppointment.date);
    while (getchar() != '\n');

    printf("Enter appointment time (HH:MM AM/PM): ");
    scanf("%s", newAppointment.time);
    while (getchar() != '\n');

    // Add the new appointment to the appointments array
    appointments[*appointmentCount] = newAppointment;
    (*appointmentCount)++;

    printf("Appointment booked successfully!\n");
}

// --------------------------------------------------------------------- Update appointment
// Function to update an appointment record
void updateAppointment(struct Appointment appointments[], int appointmentCount) {
    char searchCriteria[100]; // Maximum criteria length assumed to be 100 characters
    int choice,i;
    int updateChoice;
    int foundIndex = -1; // Initialize foundIndex to -1 (not found)

    if (appointmentCount == 0) {
        printf("No appointments available for update.\n");
        return;
    }

    // Ask the user for the search criteria type
    printf("Select the criteria to search for the appointment to update:\n");
    printf("1. Patient Name\n");
    printf("2. Date\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Ask the user for the search criteria value
    printf("Enter the search criteria: ");
    scanf("%s", searchCriteria);

    // Iterate through the appointments array based on the selected criteria
    for (i = 0; i < appointmentCount; i++) {
        if ((choice == 1 && strcmp(appointments[i].patient.name, searchCriteria) == 0) ||
            (choice == 2 && strcmp(appointments[i].date, searchCriteria) == 0)) {
            foundIndex = i;
            break; // Exit the loop when a match is found
        }
    }

    if (foundIndex != -1) {
        // Found a matching appointment, now update it
        printf("Updating appointment record:\n");

        // Ask the user what they want to update
        
        do {
            printf("Select the field to update:\n");
            printf("1. Patient Name\n");
            printf("2. Doctor Name\n");
            printf("3. Date\n");
            printf("4. Time\n");
            printf("5. Done (Exit)\n");
            printf("Enter your choice: ");
            scanf("%d", &updateChoice);

            switch (updateChoice) {
                case 1:
                    // Update the patient name in the appointment
                    printf("Enter updated patient name: ");
                    while (getchar() != '\n');
                    fgets(appointments[foundIndex].patient.name, sizeof(appointments[foundIndex].patient.name), stdin);
                    appointments[foundIndex].patient.name[strcspn(appointments[foundIndex].patient.name, "\n")] = '\0'; // Remove the newline character
                    break;
                case 2:
                    // Update the doctor name in the appointment
                    printf("Enter updated doctor name: ");
                    while (getchar() != '\n');
                    fgets(appointments[foundIndex].doctor.name, sizeof(appointments[foundIndex].doctor.name), stdin);
                    appointments[foundIndex].doctor.name[strcspn(appointments[foundIndex].doctor.name, "\n")] = '\0'; // Remove the newline character
                    break;
                case 3:
                    // Update the date in the appointment
                    printf("Enter updated appointment date (YYYY-MM-DD): ");
                    while (getchar() != '\n');
                    fgets(appointments[foundIndex].date, sizeof(appointments[foundIndex].date), stdin);
                    appointments[foundIndex].date[strcspn(appointments[foundIndex].date, "\n")] = '\0'; // Remove the newline character
                    break;
                case 4:
                    // Update the time in the appointment
                    printf("Enter updated appointment time: ");
                    while (getchar() != '\n');
                    fgets(appointments[foundIndex].time, sizeof(appointments[foundIndex].time), stdin);
                    appointments[foundIndex].time[strcspn(appointments[foundIndex].time, "\n")] = '\0'; // Remove the newline character
                    break;
                case 5:
                    // Exit the update loop
                    printf("Appointment record updated successfully!\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (updateChoice != 5);
    } else {
        printf("No matching appointment found for update.\n");
    }
}


//------------------------------------------- FUNTCTION TO DELETE APPOINTMENT -----------------------------

void deleteAppointment(struct Appointment appointments[], int *appointmentCount) {
    int i;
    char searchCriteria[100]; // Maximum criteria length assumed to be 100 characters
    int choice;
    int  foundIndex = -1; // Initialize foundIndex to -1 (not found)

    if (*appointmentCount == 0) {
        printf("No appointments available for deletion.\n");
        return;
    }
    
    // Ask the user for the search criteria type
    printf("Select the criteria to search for the appointment:\n");
    printf("1. Patient Name\n");
    printf("2. Date\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Ask the user for the search criteria value
    printf("Enter the search criteria: ");
    scanf("%s", searchCriteria);

   

    // Iterate through the appointments array based on the selected criteria
    for (i = 0; i < *appointmentCount; i++) {
        if ((choice == 1 && strcmp(appointments[i].patient.name, searchCriteria) == 0) ||
            (choice == 2 && strcmp(appointments[i].date, searchCriteria) == 0)) {
            foundIndex = i;
            break; // Exit the loop when a match is found
        }
    }

    if (foundIndex != -1) {
        // Found a matching appointment, now delete it
        for (i = foundIndex; i < (*appointmentCount - 1); i++) {
            // Shift elements to fill the gap left by the deleted appointment
            appointments[i] = appointments[i + 1];
        }
        (*appointmentCount)--;
        printf("Appointment deleted successfully.\n");
    } else {
        printf("No matching appointment found for deletion.\n");
    }
}


//--------------------------------------- FUNCTION TO DISPLAY APPOINTMENT -----------------------------

void displayAppointments(struct Appointment appointments[], int appointmentCount) {
    int i;
    if (appointmentCount == 0) {
        printf("No appointments available for display.\n");
        return;
    }

    printf("Appointments:\n");
    for (i = 0; i < appointmentCount; i++) {
        printf("Patient: %s\n", appointments[i].patient.name);
        printf("Doctor: %s\n", appointments[i].doctor.name);
        printf("Date: %s\n", appointments[i].date);
        printf("Time: %s\n", appointments[i].time);
        printf("\n");
    }
}


// ------------------------------------ FUNCTION TO SEARCH AN APPOINTMENT -------------------------------

void searchAppointments(struct Appointment appointments[], int appointmentCount) {
    char searchCriteria[100]; // Maximum criteria length assumed to be 100 characters
    int choice,i;
    int found = 0; // Flag to indicate if a match is found
    
    if (appointmentCount == 0) {
        printf("No appointments available for search.\n");
        return;
    }
    
    // Ask the user for the search criteria type
    printf("Select the criteria to search for the appointment:\n");
    printf("1. Patient Name\n");
    printf("2. Date\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Ask the user for the search criteria value
    printf("Enter the search criteria: ");
    scanf("%s", searchCriteria);

    printf("Search results:\n");
    for (i = 0; i < appointmentCount; i++) {
        if ((choice == 1 && strcmp(appointments[i].patient.name, searchCriteria) == 0) ||
            (choice == 2 && strcmp(appointments[i].date, searchCriteria) == 0)) {
            // Found a matching appointment, print its details
            printf("Patient: %s\n", appointments[i].patient.name);
            printf("Doctor: %s\n", appointments[i].doctor.name);
            printf("Date: %s\n", appointments[i].date);
            printf("Time: %s\n", appointments[i].time);
            printf("\n");
            found = 1; // Set the found flag to 1
        }
    }

    if (!found) {
        printf("No matching appointment found.\n");
    }
}


// ---------------------------------------- END -----------------------------------------------------------


// ----------------------------------- MENU DRIVENS -----------------------------------------------------

//--------------------------------------------------------------- Function to display a menu


int displayMenu(int userRole) {
    int choice;
    printf("\nHospital Management System Menu:\n");
    
    // Common options available to all roles
    printf("1. Book an Appointment\n");
    printf("5. Display Existing Records\n");
    printf("6. Search\n");
    printf("10. Exit\n");

    // Role-specific options
    switch (userRole) {
        case 1: // Admin
            printf("2. Add a Patient\n");
            printf("3. Add a Doctor\n");
            printf("4. Delete a Record\n");
            printf("7. Update a record\n");
            break;
        case 2: // Doctor
            printf("8. View Appointments\n");
            break;
        case 3: // Nurse
            printf("9. View Appointments\n");
            break;
        default:
            // Handle invalid roles
            break;
    }
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}




// -------------------------------------------------------------------Function to delete a record

void deleteRecord(struct Doctor doctors[], int *doctorCount, struct Patient patients[], int *patientCount, struct Appointment appointments[], int *appointmentCount) {
    int choice;
    printf("Select the type of record to delete:\n");
    printf("1. Doctor\n");
    printf("2. Patient\n");
    printf("3. Appointment\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            deleteDoctor(doctors, doctorCount);
            break;
        case 2:
            deletePatient(patients, patientCount);
            break;
        case 3:
            deleteAppointment(appointments, appointmentCount);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

// ----------------------------------------------------- function to update record
void displayUpdateMenu(struct Patient patients[], int patientCount, struct Doctor doctors[], int doctorCount, struct Appointment appointments[], int appointmentCount) {
    int choice;

    printf("Update Record Menu:\n");
    printf("1. Update Patient Record\n");
    printf("2. Update Doctor Record\n");
    printf("3. Update Appointment Record\n");
    printf("4. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            updatePatient(patients, patientCount);
            break;
        case 2:
            updateDoctor(doctors, doctorCount);
            break;
        case 3:
            updateAppointment(appointments, appointmentCount);
            break;
        case 4:
            // Return to the main menu
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void updatePatientForDoctor(struct Patient patients[], int patientCount) {
    char searchName[100];
    int foundIndex = -1,i;

    if (patientCount == 0) {
        printf("No patients available for update.\n");
        return;
    }

    printf("Enter the name of the patient you want to update: ");
    scanf("%s", searchName);

    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Found a matching patient, now update it
        printf("Updating patient: %s\n", patients[foundIndex].name);
        printf("Enter new age: ");
        scanf("%d", &patients[foundIndex].age);
        printf("Patient's age updated successfully!\n");
    } else {
        printf("No matching patient found for update.\n");
    }
}


void updatePatientForNurse(struct Patient patients[], int patientCount) {
    char searchName[100];
    int foundIndex = -1,i;

    if (patientCount == 0) {
        printf("No patients available for update.\n");
        return;
    }

    printf("Enter the name of the patient you want to update: ");
    scanf("%s", searchName);

    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Found a matching patient, now update it
        printf("Updating patient: %s\n", patients[foundIndex].name);
        printf("Enter new vitals for the patient:\n");
        printf("Enter new blood pressure: ");
        scanf("%lf", &patients[foundIndex].bloodPressure);
        printf("Enter new temperature: ");
        scanf("%lf", &patients[foundIndex].temperature);
        // You can add more fields to update based on the nurse's role
        printf("Patient's vitals updated successfully!\n");
    } else {
        printf("No matching patient found for update.\n");
    }
}


//----------------------------------------------------------------- Function to display existing records
void displayRecords(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount, struct Appointment appointments[], int appointmentCount) {
    int choice;
    
    printf("Select the type of records to display:\n");
    printf("1. Patients\n");
    printf("2. Doctors\n");
    printf("3. Appointments\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            displayPatients(patients, patientCount);
            break;
        case 2:
            displayDoctors(doctors, doctorCount);
            break;
        case 3:
            displayAppointments(appointments, appointmentCount);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}


//-------------------------------------------------------- Function to search for records

void search(struct Doctor doctors[], int doctorCount, struct Patient patients[], int patientCount, struct Appointment appointments[], int appointmentCount) {
    int choice;
    
    printf("Select the type of records to search within:\n");
    printf("1. Patients\n");
    printf("2. Doctors\n");
    printf("3. Appointments\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            searchPatients(patients, patientCount);
            break;
        case 2:
            searchDoctors(doctors, doctorCount);
            break;
        case 3:
            searchAppointments(appointments, appointmentCount);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}



//-------------------------------------------------------------------------- MAIN HOLDER

int main() {
    // Initialize arrays and variables
    struct User users[10];
    int numUsers = 0;
    int loggedInUser = -1; // Store the index of the currently logged-in user
    int choice,i;
    int userRole;
    char username[50];
    char password[50];
    int nurseChoice;
    int doctorChoice;

    // Initialize arrays for patients, doctors, and appointments
    struct Patient patients[100];
    int patientCount = 0;
    struct Doctor doctors[100];
    int doctorCount = 0;
    struct Appointment appointments[100];
    int appointmentCount = 0;

    // Sample users (you should implement user registration logic)
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "adminpass");
    users[0].role = 1;
    numUsers++;

    strcpy(users[1].username, "doctor");
    strcpy(users[1].password, "doctorpass");
    users[1].role = 2;
    numUsers++;

    strcpy(users[2].username, "nurse");
    strcpy(users[2].password, "nursepass");
    users[2].role = 3;
    numUsers++;

    clrscr(); // Clear the screen

    while (1) {
        if (loggedInUser == -1) {
            printf("Hospital Management System\n");
            printf("-------------------------------------------\n");
	    printf("Type 'exit' to exit or Enter your username:");
            
            
            scanf("%s", username);

            if (strcmp(username, "exit") == 0) {
                printf("\nThank you for using HMS.\n");
                printf("Created by dwellmidnight!");
                break;
            }

            printf("Enter your password: ");
            scanf("%s", password);

            for (i = 0; i < numUsers; i++) {
                if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                    loggedInUser = i; // Store the index of the logged-in user
                    printf("Login successful!\n");
                    break;
                }
            }

            if (loggedInUser == -1) {
                printf("Invalid login credentials. Please try again.\n");
            }
        }

        if (loggedInUser != -1) {
            // Display menu options based on the user's role
            userRole = users[loggedInUser].role;
            choice = displayMenu(userRole);

            // Handle menu choices
            switch (choice) {
                case 1:
                    // Implement appointment booking logic here
                    bookAppointment(appointments, &appointmentCount);
                    while (getchar() != '\n');
                    break;
                case 2:
                    // Implement patient addition logic here
                    addPatient(patients, &patientCount);
                    break;
                case 3:
                    // Implement doctor addition logic here
                    addDoctor(doctors, &doctorCount);
                    break;
                case 4:
                    // Implement record deletion logic here
                    deleteRecord(doctors, &doctorCount, patients, &patientCount, appointments, &appointmentCount);
                    break;
                case 5:
                    // Implement record display logic here
                    displayRecords(doctors, doctorCount, patients, patientCount, appointments, appointmentCount);
                    break;
                case 6:
                    // Implement search functionality here
                    search(doctors, doctorCount, patients, patientCount, appointments, appointmentCount);
                    break;
                case 7:
                    // Display the combined menu of options for updating records
                    displayUpdateMenu(patients, patientCount, doctors, doctorCount, appointments, appointmentCount);
                    break;
                case 8:
                    if (userRole == 2) {
                        // Implement Doctor-specific functionality
                        printf("Doctor-specific menu:\n");
                        printf("1. View Appointments\n");
                        printf("2. Update Patient Records\n");
                        printf("Enter your choice: ");
                        
                        scanf("%d", &doctorChoice);

                        switch (doctorChoice) {
                            case 1:
                                // Implement functionality for viewing appointments
                                displayAppointments(appointments, appointmentCount);
                                break;
                            case 2:
                                // Implement functionality for updating patient records
                                updatePatientForDoctor(patients, patientCount); // Change to update for doctor
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                                break;
                        }
                    } else {
                        printf("Invalid role for this functionality.\n");
                    }
                    break;
                case 9:
                    if (userRole == 3) {
                        // Implement Nurse-specific functionality
                        printf("Nurse-specific menu:\n");
                        printf("1. Update Patient Records\n");
                        printf("2. View Appointments\n");
                        printf("Enter your choice: ");
                        scanf("%d", &nurseChoice);

                        switch (nurseChoice) {
                            case 1:
                                // Implement functionality for updating patient records
                                updatePatientForNurse(patients, patientCount); // Change to update for nurse
                                break;
                            case 2:
                                // Implement functionality for viewing appointments
                                displayAppointments(appointments, appointmentCount);
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                                break;
                        }
                    } else {
                        printf("Invalid role for this functionality.\n");
                    }
                    break;
                case 10:
                    printf("\nLogged out. Please log in with a new account.\n");
                    loggedInUser = -1; // Log out the user
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            printf("Invalid user. Please log in with valid credentials.\n");
            break; // Terminate the program if login fails multiple times
        }
    }

    getch(); // Wait for user input
    return 0;
}
