#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  // For getch() password masking

#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_ADDRESS 100
#define MAX_QUEUE 100
#define MAX_HEAP 100
#define MAX_STACK 100

#define PATIENTS_FILE "patients.dat"
#define DOCTORS_FILE "doctors.dat"
#define MEDICINES_FILE "medicines.dat"
#define APPT_FILE "appointments.dat"
#define EMERGENCY_FILE "emergencies.dat"
#define DEPT_FILE "departments.dat"
#define HISTORY_FILE "history.dat"
#define SECURITY_FILE "security.dat"

// DATA STRUCTURES
typedef struct Patient {
    int id;
    char name[MAX_NAME];
    int age;
    char gender[10];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    char disease[100];
    char bloodGroup[5];
    int isAdmitted;
    int doctorId;
    struct Patient *next;
} Patient;

typedef struct Doctor {
    int id;
    char name[MAX_NAME];
    int age;
    char phone[MAX_PHONE];
    char specialization[50];
    char department[50];
    int isAvailable;
    int patientCount;
    struct Doctor *next;
} Doctor;

typedef struct Appointment {
    int appointmentId;
    int patientId;
    int doctorId;
    char date[20];
    char time[10];
    char status[20];
} Appointment;

typedef struct AppointmentQueue {
    Appointment data[MAX_QUEUE];
    int front, rear, size;
} AppointmentQueue;

typedef struct Emergency {
    int patientId;
    char name[MAX_NAME];
    char condition[100];
    int priority;
} Emergency;

typedef struct MaxHeap {
    Emergency arr[MAX_HEAP];
    int size;
} MaxHeap;

typedef struct Medicine {
    int id;
    char name[MAX_NAME];
    int quantity;
    float price;
    char expiryDate[20];
    struct Medicine *next;
} Medicine;

typedef struct HistoryNode {
    int actionType;
    int entityId;
    char description[250];
} HistoryNode;

typedef struct Stack {
    HistoryNode data[MAX_STACK];
    int top;
} Stack;

typedef struct DeptNode {
    int id;
    char name[MAX_NAME];
    struct DeptNode *left, *right;
} DeptNode;

// GLOBAL VARIABLES
Patient *patientHead=NULL;
Doctor *doctorHead=NULL;
Medicine *medicineHead=NULL;
Stack historyStack;
AppointmentQueue apptQueue;
MaxHeap emergencyHeap;
DeptNode *deptRoot=NULL;

int patientCount=0, doctorCount=0, medicineCount=0;
int appointmentCount=0;

int nextPatientId=1001;
int nextAppointmentId=1;
int nextDoctorId=2001;
int nextMedicineId=5001;

char systemPassword[50];
const char ENCRYPT_KEY=0x5A;

// FUNCTION DECLARATIONS
void getPassword(char *pwd);
void encryptDecryptString(char *str);
void toggleFileEncryption(const char *filename);
void loadPassword();
void savePassword();
void loginSystem();
void changePassword();

void initializeSystem();
void freeBST(DeptNode *root);
void freeAllData();
void pushHistory(int type, int id, const char *desc);
void displayHistory();

void addPatient();
Patient* findPatientById(int id);
Patient* findPatientByName(const char *name);
void deletePatient();
void searchPatientById();
void searchPatientByName();
void searchPatientByDisease();
void updatePatient();
void admitPatient();
void dischargePatient();
void displayAllPatients();
void displayAdmittedPatients();

void addDoctor();
Doctor* findDoctorById(int id);
void displayAllDoctors();
void searchDoctorBySpecialization();
void toggleDoctorAvailability();
void deleteDoctor();

void bookAppointment();
void processAppointment();
void displayAppointmentQueue();

void heapifyUp(int idx);
void heapifyDown(int idx);
void registerEmergency();
void treatEmergency();
void displayEmergencyQueue();

DeptNode* bstInsert(DeptNode *root, int id, const char *name);
DeptNode* bstSearch(DeptNode *root, int id);
void bstInorder(DeptNode *root);
void addDepartment();
void searchDepartment();
void displayDepartments();
void saveDeptHelper(DeptNode *root, FILE *f);
void saveDepartmentsToFile();
void loadDepartmentsFromFile();

void addMedicine();
void displayMedicines();
void checkLowStock();
void updateMedicineStock();
void deleteMedicine();

void savePatientsToFile();
void loadPatientsFromFile();
void saveDoctorsToFile();
void loadDoctorsFromFile();
void saveMedicinesToFile();
void loadMedicinesFromFile();
void saveOtherDataToFile();
void loadOtherDataFromFile();
void saveAllDataSecurely();
void loadAllDataSecurely();

void generatePatientReport();
void generateDoctorReport();
void displayStatistics();
void findDoctorWithMinPatients();
void findDoctorWithMaxPatients();
void findMostExpensiveMedicine();
void findCheapestMedicine();
void calculateTotalMedicineValue();
void displayOldestPatients();
void getAppointmentStatistics();
void getEmergencyStatistics();
void displayBloodGroupDistribution();
void getDiseaseDistribution();

void mainMenu();
void extendedMenu();

// MAIN FUNCTION
int main() {
    loginSystem();
    
    initializeSystem();
    printf("  [System] Loading and decrypting database files...\n");
    loadAllDataSecurely();
    printf("  [System] Secure Load Complete!\n\n");
    
    int choice;
    do {
        mainMenu();
        scanf("%d", &choice); 
        printf("Invalid Input!\n");
        while(getchar()!='\n'); 
        continue;
        
        switch(choice) {
            case 1: addPatient(); break;
            case 2: deletePatient(); break;
            case 3: searchPatientById(); break;
            case 4: searchPatientByName(); break;
            case 5: searchPatientByDisease(); break;
            case 6: updatePatient(); break;
            case 7: admitPatient(); break;
            case 8: dischargePatient(); break;
            case 9: displayAllPatients(); break;
            case 10: displayAdmittedPatients(); break;
            case 11: addDoctor(); break;
            case 12: searchDoctorBySpecialization(); break;
            case 13: toggleDoctorAvailability(); break;
            case 14: deleteDoctor(); break;
            case 15: displayAllDoctors(); break;
            case 16: bookAppointment(); break;
            case 17: processAppointment(); break;
            case 18: displayAppointmentQueue(); break;
            case 19: registerEmergency(); break;
            case 20: treatEmergency(); break;
            case 21: displayEmergencyQueue(); break;
            case 22: addDepartment(); break;
            case 23: searchDepartment(); break;
            case 24: displayDepartments(); break;
            case 25: addMedicine(); break;
            case 26: displayMedicines(); break;
            case 27: checkLowStock(); break;
            case 28: updateMedicineStock(); break;
            case 29: deleteMedicine(); break;
            case 30: 
                saveAllDataSecurely(); 
                printf("  ALL DATA SAVED AND ENCRYPTED SUCCESSFULLY.\n\n");
                break;
            case 31: 
                freeAllData();
                patientCount=0; doctorCount=0; medicineCount=0;
                initializeSystem();
                loadAllDataSecurely();
                printf("  ALL DATA DECRYPTED AND LOADED SUCCESSFULLY.\n\n");
                break;
            case 32: displayHistory(); break;
            case 33: generatePatientReport(); break;
            case 34: generateDoctorReport(); break;
            case 35: displayStatistics(); break;
            case 36: extendedMenu(); break;
            case 37: changePassword(); break;
            case 0: 
                printf("\n  [System Shutdown] Encrypting all data to database...\n");
                saveAllDataSecurely();
                freeAllData();
                printf("  DATABASE SECURED. EXITING SYSTEM. GOODBYE!\n\n"); 
                break;
            default: printf("  INVALID CHOICE! PLEASE TRY AGAIN.\n\n");
        }
    } while(choice!=0);
    
    return 0;
}

// SECTION 1: SECURITY & ENCRYPTION
void getPassword(char *pwd) {
    int i=0;
    char ch;
    while(1) {
        ch=getch();
        if(ch=='\r'||ch=='\n') {
            pwd[i]='\0';
            break;
        } else if(ch=='\b') {
            if(i>0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++]=ch;
            printf("*");
        }
    }
    printf("\n");
}

void encryptDecryptString(char *str) {
    for(int i=0; str[i]!='\0'; i++) {
        str[i]^=ENCRYPT_KEY;
    }
}

void toggleFileEncryption(const char *filename) {
    FILE *f=fopen(filename, "rb");
    if(!f) return;
    
    fseek(f, 0, SEEK_END);
    long size=ftell(f);
    if(size<=0) { fclose(f); return; }
    fseek(f, 0, SEEK_SET);
    
    char *buffer=(char*)malloc(size);
    if(!buffer) { fclose(f); return; }
    
    fread(buffer, 1, size, f);
    fclose(f);

    for(long i=0; i<size; i++) {
        buffer[i]^=ENCRYPT_KEY;
    }

    f=fopen(filename, "wb");
    if(f) {
        fwrite(buffer, 1, size, f);
        fclose(f);
    }
    free(buffer);
}

void loadPassword() {
    FILE *f=fopen(SECURITY_FILE, "r");
    if(f) {
        fscanf(f, "%49s", systemPassword);
        encryptDecryptString(systemPassword); 
        fclose(f);
    } else {
        strcpy(systemPassword, "admin"); 
        FILE *fw=fopen(SECURITY_FILE, "w");
        if(fw) {
            char temp[50];
            strcpy(temp, systemPassword);
            encryptDecryptString(temp);
            fprintf(fw, "%s", temp);
            fclose(fw);
        }
    }
}

void savePassword() {
    FILE *f=fopen(SECURITY_FILE, "w");
    if(f) {
        char temp[50];
        strcpy(temp, systemPassword);
        encryptDecryptString(temp); 
        fprintf(f, "%s", temp);
        fclose(f);
    }
}

void loginSystem() {
    char inputPwd[50];
    loadPassword();
    printf("         SECURE HOSPITAL MANAGEMENT SYSTEM LOGIN\n");
    
    while(1) {
        printf("  Enter System Password: ");
        getPassword(inputPwd);
        
        if(strcmp(inputPwd, systemPassword)==0) {
            printf("  [ACCESS GRANTED] Decrypting Database...\n\n");
            break;
        } else {
            printf("  [ACCESS DENIED] Incorrect Password! Try again.\n\n");
        }
    }
}

void changePassword() {
    char oldPwd[50], newPwd[50];
    printf("\n  === CHANGE SECURITY PASSWORD ===\n");
    printf("  Enter Current Password: ");
    getPassword(oldPwd);
    
    if(strcmp(oldPwd, systemPassword)==0) {
        printf("  Enter New Password: ");
        getPassword(newPwd);
        strcpy(systemPassword, newPwd);
        savePassword();
        printf("  PASSWORD CHANGED SECURELY!\n\n");
    } else {
        printf("  INCORRECT CURRENT PASSWORD! Operation cancelled.\n\n");
    }
}

// SECTION 2: CORE SYSTEM & HISTORY (STACK)
void initializeSystem() {
    historyStack.top=-1;
    apptQueue.front=0;
    apptQueue.rear=-1;
    apptQueue.size=0;
    emergencyHeap.size=0;
}

void freeBST(DeptNode *root) {
    if(!root) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

void freeAllData() {
    Patient *pCurr=patientHead;
    while(pCurr) {
        Patient *pNext=pCurr->next;
        free(pCurr);
        pCurr=pNext;
    }
    patientHead=NULL;

    Doctor *dCurr=doctorHead;
    while(dCurr) {
        Doctor *dNext=dCurr->next;
        free(dCurr);
        dCurr=dNext;
    }
    doctorHead=NULL;

    Medicine *mCurr=medicineHead;
    while(mCurr) {
        Medicine *mNext=mCurr->next;
        free(mCurr);
        mCurr=mNext;
    }
    medicineHead=NULL;

    freeBST(deptRoot);
    deptRoot=NULL;
}

void pushHistory(int type, int id, const char *desc) {
    if(historyStack.top<MAX_STACK-1) {
        historyStack.top++;
        historyStack.data[historyStack.top].actionType=type;
        historyStack.data[historyStack.top].entityId=id;
        strncpy(historyStack.data[historyStack.top].description, desc, sizeof(historyStack.data[historyStack.top].description)-1);
        historyStack.data[historyStack.top].description[sizeof(historyStack.data[historyStack.top].description)-1]='\0';
    }
}

void displayHistory() {
    printf("\n       ACTION HISTORY (Stack - LIFO)\n");
    printf("  %-80s\n", "Description");
    printf("  %s\n", "------------------------------------------------------------------------------------");
    for(int i=historyStack.top; i>=0 && i>=historyStack.top-30; i--) {
        printf("  [%d] %s\n", historyStack.top-i, historyStack.data[i].description);
    }
    printf("  Total History Entries: %d\n\n", historyStack.top+1);
}

// SECTION 3: PATIENT MANAGEMENT (LINKED LIST)
void addPatient() {
    char tempPhone[MAX_PHONE];
    printf("  Phone: "); 
    scanf(" %14s", tempPhone);

    Patient *curr=patientHead;
    int found=0;
    while(curr) {
        if(strcmp(curr->phone, tempPhone)==0) {
            if(!found) {
                printf("\n  [WARNING] FOLLOWING PATIENT(S) ALREADY EXIST WITH THIS NUMBER:\n");
            }
            printf("  -> Name: %-15s | ID: %d | Age: %d | Disease: %s\n", curr->name, curr->id, curr->age, curr->disease);
            found=1;
        }
        curr=curr->next;
    }

    if(found) {
        char choice;
        printf("\n  Do you want to add another family member with this number? (Y/N): ");
        scanf(" %c", &choice);
        if(choice=='N'||choice=='n') {
            printf("  PATIENT REGISTRATION CANCELLED.\n\n");
            return;
        }
        printf("\n  Proceeding to register new family member...\n");
    }

    Patient *new=(Patient*)malloc(sizeof(Patient));
    new->id=nextPatientId++;
    strcpy(new->phone, tempPhone);
    
    printf("  Name: "); scanf(" %[^\n]", new->name);
    printf("  Age: "); scanf("%d", &new->age);
    printf("  Gender (M/F): "); scanf(" %9s", new->gender);
    printf("  Address: "); scanf(" %[^\n]", new->address);
    printf("  Disease: "); scanf(" %[^\n]", new->disease);
    printf("  Blood Group (A+/A-/B+/B-/O+/O-/AB+/AB-): "); scanf(" %4s", new->bloodGroup);
    
    new->isAdmitted=0;
    new->doctorId=0;
    new->next=NULL;
    
    if(!patientHead) patientHead=new;
    else {
        Patient *tail=patientHead;
        while(tail->next) tail=tail->next;
        tail->next=new;
    }
    patientCount++;
    
    char desc[150];
    sprintf(desc, "Added patient: %s (ID: %d)", new->name, new->id);
    pushHistory(1, new->id, desc);
    printf("  PATIENT ADDED SUCCESSFULLY. ID: %d\n\n", new->id);
}

Patient* findPatientById(int id) {
    Patient *curr=patientHead;
    while(curr) {
        if(curr->id==id) return curr;
        curr=curr->next;
    }
    return NULL;
}

Patient* findPatientByName(const char *name) {
    Patient *curr=patientHead;
    while(curr) {
        if(strcmp(curr->name, name)==0) return curr;
        curr=curr->next;
    }
    return NULL;
}

void deletePatient() {
    int id;
    printf("  Patient ID to delete: "); scanf("%d", &id);
    
    Patient *curr=patientHead, *prev=NULL;
    while(curr && curr->id!=id) {
        prev=curr;
        curr=curr->next;
    }
    
    if(!curr) { printf("  PATIENT NOT FOUND.\n\n"); return; }
    
    if(!prev) patientHead=curr->next;
    else prev->next=curr->next;
    
    char desc[150];
    sprintf(desc, "Deleted patient: %s (ID: %d)", curr->name, curr->id);
    pushHistory(1, id, desc);
    
    free(curr);
    patientCount--;
    printf("  PATIENT DELETED SUCCESSFULLY.\n\n");
}

void searchPatientById() {
    int id;
    printf("  Enter Patient ID: "); scanf("%d", &id);
    Patient *p=findPatientById(id);
    if(p) {
        printf("\n  PATIENT FOUND:\n");
        printf("  ID: %d\n", p->id);
        printf("  Name: %s\n", p->name);
        printf("  Age: %d\n", p->age);
        printf("  Gender: %s\n", p->gender);
        printf("  Phone: %s\n", p->phone);
        printf("  Address: %s\n", p->address);
        printf("  Disease: %s\n", p->disease);
        printf("  Blood Group: %s\n", p->bloodGroup);
        printf("  Status: %s\n\n", p->isAdmitted ? "Admitted" : "Outpatient");
    } else printf("  PATIENT NOT FOUND.\n\n");
}

void searchPatientByName() {
    char name[MAX_NAME];
    printf("  Enter Patient Name: "); scanf(" %[^\n]", name);
    Patient *p=findPatientByName(name);
    if(p) {
        printf("\n  FOUND: ID %d | Age: %d | Disease: %s | Status: %s\n\n", 
               p->id, p->age, p->disease, p->isAdmitted ? "Admitted" : "Outpatient");
    } else printf("  NOT FOUND.\n\n");
}

void searchPatientByDisease() {
    char disease[100];
    printf("  Enter Disease: "); scanf(" %[^\n]", disease);
    
    printf("\n       PATIENTS WITH %s    \n", disease);
    printf("  %-6s %-20s %-6s %-10s\n", "ID", "Name", "Age", "Status");
    printf("  %s\n", "-----------------------------------");
    
    Patient *curr=patientHead;
    int count=0;
    while(curr) {
        if(strcmp(curr->disease, disease)==0) {
            printf("  %-6d %-20s %-6d %-10s\n", curr->id, curr->name, curr->age,
                   curr->isAdmitted ? "Admitted" : "Outpatient");
            count++;
        }
        curr=curr->next;
    }
    printf("  Total Found: %d\n\n", count);
}

void updatePatient() {
    int id, newAge;
    printf("  Patient ID: "); scanf("%d", &id);
    Patient *p=findPatientById(id);
    if(!p) { printf("  PATIENT NOT FOUND.\n\n"); return; }
    
    printf("  Current Name: %s\n", p->name);
    printf("  New Age: "); scanf("%d", &newAge);
    printf("  New Disease: "); scanf(" %[^\n]", p->disease);
    
    p->age=newAge;
    
    char desc[250];
    snprintf(desc, sizeof(desc), "Updated patient: %s (Age: %d, Disease: %s)", p->name, newAge, p->disease);
    pushHistory(1, id, desc);
    printf("  PATIENT UPDATED SUCCESSFULLY.\n\n");
}

void admitPatient() {
    int id, docId;
    printf("  Patient ID: "); scanf("%d", &id);
    printf("  Doctor ID: "); scanf("%d", &docId);
    
    Patient *p=findPatientById(id);
    if(!p) { printf("  PATIENT NOT FOUND.\n\n"); return; }
    
    Doctor *d=NULL;
    Doctor *curr=doctorHead;
    while(curr) {
        if(curr->id==docId) { d=curr; break; }
        curr=curr->next;
    }
    
    if(!d) { printf("  DOCTOR NOT FOUND.\n\n"); return; }
    
    p->isAdmitted=1;
    p->doctorId=docId;
    d->patientCount++;
    
    char desc[150];
    sprintf(desc, "Admitted patient: %s to Doctor %s", p->name, d->name);
    pushHistory(1, id, desc);
    printf("  PATIENT ADMITTED SUCCESSFULLY.\n\n");
}

void dischargePatient() {
    int id;
    printf("  Patient ID: "); scanf("%d", &id);
    Patient *p=findPatientById(id);
    if(!p) { printf("  PATIENT NOT FOUND.\n\n"); return; }
    
    if(p->doctorId) {
        Doctor *curr=doctorHead;
        while(curr) {
            if(curr->id==p->doctorId) {
                if(curr->patientCount>0) curr->patientCount--;
                break;
            }
            curr=curr->next;
        }
    }
    
    p->isAdmitted=0;
    p->doctorId=0;
    
    char desc[150];
    sprintf(desc, "Discharged patient: %s", p->name);
    pushHistory(1, id, desc);
    printf("  PATIENT DISCHARGED SUCCESSFULLY.\n\n");
}

void displayAllPatients() {
    printf("\n  === ALL PATIENTS (Linked List) ===\n");
    printf("  %-6s %-20s %-6s %-10s %-15s %-20s\n", "ID", "Name", "Age", "Phone", "Status", "Disease");
    printf("  %s\n", "--------------------------------------------------------------------------------");
    Patient *curr=patientHead;
    int count=0;
    while(curr && count<100) {
        printf("  %-6d %-20s %-6d %-10s %-15s %-20s\n", curr->id, curr->name, curr->age, curr->phone,
               curr->isAdmitted ? "Admitted" : "Outpatient", curr->disease);
        curr=curr->next;
        count++;
    }
    printf("  Total Patients: %d\n\n", patientCount);
}

void displayAdmittedPatients() {
    printf("\n  === ADMITTED PATIENTS ===\n");
    printf("  %-6s %-20s %-20s %-8s\n", "ID", "Name", "Disease", "Doctor ID");
    printf("  %s\n", "-------------------------------------------");
    Patient *curr=patientHead;
    int count=0;
    while(curr) {
        if(curr->isAdmitted) {
            printf("  %-6d %-20s %-20s %-8d\n", curr->id, curr->name, curr->disease, curr->doctorId);
            count++;
        }
        curr=curr->next;
    }
    printf("  Total Admitted: %d\n\n", count);
}

// SECTION 4: DOCTOR MANAGEMENT (LINKED LIST)
void addDoctor() {
    Doctor *new=(Doctor*)malloc(sizeof(Doctor));
    new->id=nextDoctorId++;
    printf("  Name: "); scanf(" %[^\n]", new->name);
    printf("  Age: "); scanf("%d", &new->age);
    printf("  Phone: "); scanf(" %14s", new->phone);
    printf("  Specialization: "); scanf(" %[^\n]", new->specialization);
    printf("  Department: "); scanf(" %[^\n]", new->department);
    
    new->isAvailable=1;
    new->patientCount=0;
    new->next=NULL;
    
    if(!doctorHead) doctorHead=new;
    else {
        Doctor *curr=doctorHead;
        while(curr->next) curr=curr->next;
        curr->next=new;
    }
    doctorCount++;
    
    char desc[150];
    sprintf(desc, "Added doctor: %s - %s (ID: %d)", new->name, new->specialization, new->id);
    pushHistory(5, new->id, desc);
    printf("  DOCTOR ADDED SUCCESSFULLY. ID: %d\n\n", new->id);
}

Doctor* findDoctorById(int id) {
    Doctor *curr=doctorHead;
    while(curr) {
        if(curr->id==id) return curr;
        curr=curr->next;
    }
    return NULL;
}

void displayAllDoctors() {
    printf("\n  === ALL DOCTORS (Linked List) ===\n");
    printf("  %-6s %-20s %-20s %-15s %-10s\n", "ID", "Name", "Specialization", "Department", "Available");
    printf("  %s\n", "------------------------------------------------------------------");
    Doctor *curr=doctorHead;
    int count=0;
    while(curr) {
        printf("  %-6d %-20s %-20s %-15s %-10s\n", curr->id, curr->name, curr->specialization,
               curr->department, curr->isAvailable ? "Yes" : "No");
        count++;
        curr=curr->next;
    }
    printf("  Total Doctors: %d\n\n", count);
}

void searchDoctorBySpecialization() {
    char spec[50];
    printf("  Enter Specialization: "); scanf(" %[^\n]", spec);
    
    printf("\n  === DOCTORS - %s ===\n", spec);
    printf("  %-6s %-20s %-15s %-10s\n", "ID", "Name", "Department", "Available");
    printf("  %s\n", "-----------------------------------");
    
    Doctor *curr=doctorHead;
    int count=0;
    while(curr) {
        if(strcmp(curr->specialization, spec)==0) {
            printf("  %-6d %-20s %-15s %-10s\n", curr->id, curr->name, curr->department,
                   curr->isAvailable ? "Yes" : "No");
            count++;
        }
        curr=curr->next;
    }
    printf("  Total Found: %d\n\n", count);
}

void toggleDoctorAvailability() {
    int id;
    printf("  Doctor ID: "); scanf("%d", &id);
    Doctor *d=findDoctorById(id);
    if(!d) { printf("  DOCTOR NOT FOUND.\n\n"); return; }
    
    d->isAvailable=!d->isAvailable;
    printf("  Availability changed to: %s\n\n", d->isAvailable ? "Available" : "Not Available");
}

void deleteDoctor() {
    int id;
    printf("  Doctor ID: "); scanf("%d", &id);
    
    Doctor *curr=doctorHead, *prev=NULL;
    while(curr && curr->id!=id) {
        prev=curr;
        curr=curr->next;
    }
    
    if(!curr) { printf("  DOCTOR NOT FOUND.\n\n"); return; }
    
    Patient *p=patientHead;
    while(p) {
        if(p->doctorId==id) {
            p->doctorId=0; 
        }
        p=p->next;
    }
    
    if(!prev) doctorHead=curr->next;
    else prev->next=curr->next;
    
    free(curr);
    doctorCount--;
    printf("  DOCTOR DELETED.\n\n");
}

// SECTION 5: APPOINTMENT MANAGEMENT (QUEUE - FIFO)
void bookAppointment() {
    if(apptQueue.size==MAX_QUEUE) {
        printf("  APPOINTMENT QUEUE FULL!\n\n");
        return;
    }
    
    int patId, docId;
    char date[20], time[10];
    printf("  Patient ID: "); scanf("%d", &patId);
    printf("  Doctor ID: "); scanf("%d", &docId);
    
    Patient *p=findPatientById(patId);
    Doctor *d=findDoctorById(docId);
    
    if(!p) { printf("  ERROR: PATIENT ID DOES NOT EXIST.\n\n"); return; }
    if(!d) { printf("  ERROR: DOCTOR ID DOES NOT EXIST.\n\n"); return; }
    if(!d->isAvailable) { printf("  ERROR: DOCTOR IS CURRENTLY UNAVAILABLE.\n\n"); return; }

    printf("  Date (DD/MM/YYYY): "); scanf(" %19s", date);
    printf("  Time (HH:MM): "); scanf(" %9s", time);
    
    apptQueue.rear=(apptQueue.rear+1)%MAX_QUEUE;
    apptQueue.data[apptQueue.rear].appointmentId=nextAppointmentId++;
    apptQueue.data[apptQueue.rear].patientId=patId;
    apptQueue.data[apptQueue.rear].doctorId=docId;
    strcpy(apptQueue.data[apptQueue.rear].date, date);
    strcpy(apptQueue.data[apptQueue.rear].time, time);
    strcpy(apptQueue.data[apptQueue.rear].status, "Pending");
    apptQueue.size++;
    appointmentCount++;
    
    printf("  APPOINTMENT BOOKED. Position in queue: %d\n\n", apptQueue.size);
}

void processAppointment() {
    if(apptQueue.size==0) {
        printf("  NO APPOINTMENTS IN QUEUE.\n\n");
        return;
    }
    
    Appointment a=apptQueue.data[apptQueue.front];
    apptQueue.front=(apptQueue.front+1)%MAX_QUEUE;
    apptQueue.size--;
    
    printf("  PROCESSED APPOINTMENT:\n");
    printf("  Appointment ID: %d | Patient: %d | Doctor: %d\n", a.appointmentId, a.patientId, a.doctorId);
    printf("  Date: %s | Time: %s | Status: Completed\n\n", a.date, a.time);
}

void displayAppointmentQueue() {
    printf("\n  === APPOINTMENT QUEUE (%d/%d) (FIFO) ===\n", apptQueue.size, MAX_QUEUE);
    printf("  %-5s %-10s %-10s %-12s %-8s %-10s\n", "Pos", "PatID", "DocID", "Date", "Time", "Status");
    printf("  %s\n", "-------------------------------------");
    for(int i=0; i<apptQueue.size; i++) {
        int idx=(apptQueue.front+i)%MAX_QUEUE;
        printf("  %-5d %-10d %-10d %-12s %-8s %-10s\n", i+1, apptQueue.data[idx].patientId,
               apptQueue.data[idx].doctorId, apptQueue.data[idx].date, apptQueue.data[idx].time,
               apptQueue.data[idx].status);
    }
    printf("\n");
}

// SECTION 6: EMERGENCY MANAGEMENT (MAX HEAP)
void heapifyUp(int idx) {
    while(idx>0) {
        int parent=(idx-1)/2;
        if(emergencyHeap.arr[parent].priority<emergencyHeap.arr[idx].priority) {
            Emergency tmp=emergencyHeap.arr[parent];
            emergencyHeap.arr[parent]=emergencyHeap.arr[idx];
            emergencyHeap.arr[idx]=tmp;
            idx=parent;
        } else break;
    }
}

void heapifyDown(int idx) {
    int largest=idx;
    int l=2*idx+1, r=2*idx+2;
    if(l<emergencyHeap.size && emergencyHeap.arr[l].priority>emergencyHeap.arr[largest].priority) 
        largest=l;
    if(r<emergencyHeap.size && emergencyHeap.arr[r].priority>emergencyHeap.arr[largest].priority) 
        largest=r;
    if(largest!=idx) {
        Emergency tmp=emergencyHeap.arr[idx];
        emergencyHeap.arr[idx]=emergencyHeap.arr[largest];
        emergencyHeap.arr[largest]=tmp;
        heapifyDown(largest);
    }
}

void registerEmergency() {
    if(emergencyHeap.size>=MAX_HEAP) {
        printf("  EMERGENCY QUEUE FULL!\n\n");
        return;
    }
    
    int id, priority;
    char name[MAX_NAME], condition[100];
    printf("  Patient ID: "); scanf("%d", &id);
    printf("  Name: "); scanf(" %[^\n]", name);
    printf("  Condition: "); scanf(" %[^\n]", condition);
    printf("  Priority (1=Normal, 2=Serious, 3=Critical): "); scanf("%d", &priority);
    
    emergencyHeap.arr[emergencyHeap.size].patientId=id;
    strcpy(emergencyHeap.arr[emergencyHeap.size].name, name);
    strcpy(emergencyHeap.arr[emergencyHeap.size].condition, condition);
    emergencyHeap.arr[emergencyHeap.size].priority=priority;
    emergencyHeap.size++;
    heapifyUp(emergencyHeap.size-1);
    
    const char *prioStr=priority==3 ? "CRITICAL" : priority==2 ? "SERIOUS" : "NORMAL";
    printf("  EMERGENCY REGISTERED. Priority: %s\n\n", prioStr);
}

void treatEmergency() {
    if(emergencyHeap.size==0) {
        printf("  NO EMERGENCY PATIENTS.\n\n");
        return;
    }
    
    Emergency ep=emergencyHeap.arr[0];
    emergencyHeap.arr[0]=emergencyHeap.arr[--emergencyHeap.size];
    heapifyDown(0);
    
    const char *prioStr=ep.priority==3 ? "CRITICAL" : ep.priority==2 ? "SERIOUS" : "NORMAL";
    printf("  NOW TREATING: %s\n", ep.name);
    printf("  Priority: %s | Condition: %s\n", prioStr, ep.condition);
    printf("  Status: Under Treatment\n\n");
}

void displayEmergencyQueue() {
    printf("\n  === EMERGENCY QUEUE (%d) (Max Heap - Priority Based) ===\n", emergencyHeap.size);
    printf("  %-20s %-20s %-10s\n", "Name", "Condition", "Priority");
    printf("  %s\n", "---------------------------------------");
    for(int i=0; i<emergencyHeap.size; i++) {
        const char *prioStr=emergencyHeap.arr[i].priority==3 ? "CRITICAL" : 
                              emergencyHeap.arr[i].priority==2 ? "SERIOUS" : "NORMAL";
        printf("  %-20s %-20s %-10s\n", emergencyHeap.arr[i].name,
               emergencyHeap.arr[i].condition, prioStr);
    }
    printf("\n");
}

// SECTION 7: DEPARTMENT MANAGEMENT (BST)
DeptNode* bstInsert(DeptNode *root, int id, const char *name) {
    if(!root) {
        DeptNode *node=(DeptNode*)malloc(sizeof(DeptNode));
        node->id=id;
        strcpy(node->name, name);
        node->left=node->right=NULL;
        return node;
    }
    if(id<root->id) root->left=bstInsert(root->left, id, name);
    else if(id>root->id) root->right=bstInsert(root->right, id, name);
    return root;
}

DeptNode* bstSearch(DeptNode *root, int id) {
    if(!root || root->id==id) return root;
    if(id<root->id) return bstSearch(root->left, id);
    return bstSearch(root->right, id);
}

void bstInorder(DeptNode *root) {
    if(!root) return;
    bstInorder(root->left);
    printf("  Dept %d: %s\n", root->id, root->name);
    bstInorder(root->right);
}

void addDepartment() {
    int id;
    char name[MAX_NAME];
    printf("  Department ID: "); scanf("%d", &id);
    printf("  Department Name: "); scanf(" %[^\n]", name);
    deptRoot=bstInsert(deptRoot, id, name);
    printf("  DEPARTMENT ADDED.\n\n");
}

void searchDepartment() {
    int id;
    printf("  Department ID: "); scanf("%d", &id);
    DeptNode *d=bstSearch(deptRoot, id);
    if(d) printf("  Found: %s\n\n", d->name);
    else printf("  DEPARTMENT NOT FOUND.\n\n");
}

void displayDepartments() {
    printf("\n  === DEPARTMENTS (Binary Search Tree - Sorted by ID) ===\n");
    if(!deptRoot) {
        printf("  No departments found.\n\n");
        return;
    }
    bstInorder(deptRoot);
    printf("\n");
}

void saveDeptHelper(DeptNode *root, FILE *f) {
    if(!root) return;
    fprintf(f, "%d|%s\n", root->id, root->name);
    saveDeptHelper(root->left, f);
    saveDeptHelper(root->right, f);
}

void saveDepartmentsToFile() {
    FILE *f=fopen(DEPT_FILE, "w");
    if(!f) return;
    saveDeptHelper(deptRoot, f);
    fclose(f);
}

void loadDepartmentsFromFile() {
    FILE *f=fopen(DEPT_FILE, "r");
    if(!f) return;
    int id;
    char name[MAX_NAME];
    while(fscanf(f, "%d|%[^\n]\n", &id, name)==2) {
        deptRoot=bstInsert(deptRoot, id, name);
    }
    fclose(f);
}

// SECTION 8: MEDICINE MANAGEMENT (LINKED LIST)
void addMedicine() {
    Medicine *new=(Medicine*)malloc(sizeof(Medicine));
    new->id=nextMedicineId++;
    printf("  Name: "); scanf(" %[^\n]", new->name);
    printf("  Quantity: "); scanf("%d", &new->quantity);
    printf("  Price: "); scanf("%f", &new->price);
    printf("  Expiry Date (MM/YYYY): "); scanf(" %19s", new->expiryDate);
    new->next=NULL;
    
    if(!medicineHead) medicineHead=new;
    else {
        Medicine *curr=medicineHead;
        while(curr->next) curr=curr->next;
        curr->next=new;
    }
    medicineCount++;
    
    char desc[150];
    sprintf(desc, "Added medicine: %s (Qty: %d, Price: %.2f)", new->name, new->quantity, new->price);
    pushHistory(3, new->id, desc);
    printf("  MEDICINE ADDED SUCCESSFULLY. ID: %d\n\n", new->id);
}

void displayMedicines() {
    printf("\n  === MEDICINE INVENTORY (Linked List) ===\n");
    printf("  %-6s %-25s %-10s %-8s %-12s\n", "ID", "Name", "Qty", "Price", "Expiry");
    printf("  %s\n", "---------------------------------------------------");
    Medicine *curr=medicineHead;
    int count=0;
    while(curr) {
        printf("  %-6d %-25s %-10d %-8.2f %-12s\n", curr->id, curr->name, curr->quantity, 
               curr->price, curr->expiryDate);
        count++;
        curr=curr->next;
    }
    printf("  Total Medicines: %d\n\n", count);
}

void checkLowStock() {
    int threshold;
    printf("  Stock Threshold: "); scanf("%d", &threshold);
    printf("\n  === LOW STOCK MEDICINES ===\n");
    printf("  %-6s %-25s %-10s %-8s\n", "ID", "Name", "Current Qty", "Price");
    printf("  %s\n", "-----------------------------------");
    
    Medicine *curr=medicineHead;
    int found=0;
    while(curr) {
        if(curr->quantity<=threshold) {
            printf("  %-6d %-25s %-10d %-8.2f\n", curr->id, curr->name, curr->quantity, curr->price);
            found++;
        }
        curr=curr->next;
    }
    if(found==0) printf("  All medicines in good stock.\n");
    printf("  Alert Items: %d\n\n", found);
}

void updateMedicineStock() {
    int id, newQty;
    printf("  Medicine ID: "); scanf("%d", &id);
    printf("  New Quantity: "); scanf("%d", &newQty);
    
    Medicine *curr=medicineHead;
    while(curr) {
        if(curr->id==id) {
            int oldQty=curr->quantity;
            curr->quantity=newQty;
            printf("  UPDATED: %d -> %d units\n\n", oldQty, newQty);
            return;
        }
        curr=curr->next;
    }
    printf("  MEDICINE NOT FOUND.\n\n");
}

void deleteMedicine() {
    int id;
    printf("  Medicine ID: "); scanf("%d", &id);
    
    Medicine *curr=medicineHead, *prev=NULL;
    while(curr && curr->id!=id) {
        prev=curr;
        curr=curr->next;
    }
    
    if(!curr) { printf("  MEDICINE NOT FOUND.\n\n"); return; }
    
    if(!prev) medicineHead=curr->next;
    else prev->next=curr->next;
    
    free(curr);
    medicineCount--;
    printf("  MEDICINE DELETED.\n\n");
}

// SECTION 9: FILE HANDLING (SECURE DATA STORAGE)
void savePatientsToFile() {
    FILE *f=fopen(PATIENTS_FILE, "w");
    if(!f) return;
    fprintf(f, "%d\n", patientCount);
    Patient *curr=patientHead;
    while(curr) {
        fprintf(f, "%d|%s|%d|%s|%s|%s|%s|%s|%d|%d\n", curr->id, curr->name, curr->age, curr->gender,
                curr->phone, curr->address, curr->disease, curr->bloodGroup, curr->isAdmitted, curr->doctorId);
        curr=curr->next;
    }
    fclose(f);
}

void loadPatientsFromFile() {
    FILE *f=fopen(PATIENTS_FILE, "r");
    if(!f) return;
    int count;
    if(fscanf(f, "%d\n", &count)!=1) { fclose(f); return; }
    for(int i=0; i<count; i++) {
        Patient *new=(Patient*)malloc(sizeof(Patient));
        fscanf(f, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &new->id, new->name, &new->age,
               new->gender, new->phone, new->address, new->disease, new->bloodGroup, &new->isAdmitted, &new->doctorId);
        new->next=NULL;
        if(!patientHead) patientHead=new;
        else {
            Patient *curr=patientHead;
            while(curr->next) curr=curr->next;
            curr->next=new;
        }
        patientCount++;
        if(new->id>=nextPatientId) nextPatientId=new->id+1;
    }
    fclose(f);
}

void saveDoctorsToFile() {
    FILE *f=fopen(DOCTORS_FILE, "w");
    if(!f) return;
    fprintf(f, "%d\n", doctorCount);
    Doctor *curr=doctorHead;
    while(curr) {
        fprintf(f, "%d|%s|%d|%s|%s|%s|%d|%d\n", curr->id, curr->name, curr->age, curr->phone, 
                curr->specialization, curr->department, curr->isAvailable, curr->patientCount);
        curr=curr->next;
    }
    fclose(f);
}

void loadDoctorsFromFile() {
    FILE *f=fopen(DOCTORS_FILE, "r");
    if(!f) return;
    int count;
    if(fscanf(f, "%d\n", &count)!=1) { fclose(f); return; }
    for(int i=0; i<count; i++) {
        Doctor *new=(Doctor*)malloc(sizeof(Doctor));
        fscanf(f, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%d\n", &new->id, new->name, &new->age, 
               new->phone, new->specialization, new->department, &new->isAvailable, &new->patientCount);
        new->next=NULL;
        if(!doctorHead) doctorHead=new;
        else {
            Doctor *curr=doctorHead;
            while(curr->next) curr=curr->next;
            curr->next=new;
        }
        doctorCount++;
        if(new->id>=nextDoctorId) nextDoctorId=new->id+1;
    }
    fclose(f);
}

void saveMedicinesToFile() {
    FILE *f=fopen(MEDICINES_FILE, "w");
    if(!f) return;
    fprintf(f, "%d\n", medicineCount);
    Medicine *curr=medicineHead;
    while(curr) {
        fprintf(f, "%d|%s|%d|%f|%s\n", curr->id, curr->name, curr->quantity, curr->price, 
                curr->expiryDate);
        curr=curr->next;
    }
    fclose(f);
}

void loadMedicinesFromFile() {
    FILE *f=fopen(MEDICINES_FILE, "r");
    if(!f) return;
    int count;
    if(fscanf(f, "%d\n", &count)!=1) { fclose(f); return; }
    for(int i=0; i<count; i++) {
        Medicine *new=(Medicine*)malloc(sizeof(Medicine));
        fscanf(f, "%d|%[^|]|%d|%f|%[^\n]\n", &new->id, new->name, &new->quantity, 
               &new->price, new->expiryDate);
        new->next=NULL;
        if(!medicineHead) medicineHead=new;
        else {
            Medicine *curr=medicineHead;
            while(curr->next) curr=curr->next;
            curr->next=new;
        }
        medicineCount++;
        if(new->id>=nextMedicineId) nextMedicineId=new->id+1;
    }
    fclose(f);
}

void saveOtherDataToFile() {
    FILE *fq=fopen(APPT_FILE, "w");
    if(fq) {
        fprintf(fq, "%d|%d|%d|%d\n", apptQueue.size, apptQueue.front, apptQueue.rear, nextAppointmentId);
        for(int i=0; i<apptQueue.size; i++) {
            int idx=(apptQueue.front+i)%MAX_QUEUE;
            fprintf(fq, "%d|%d|%d|%s|%s|%s\n", apptQueue.data[idx].appointmentId, apptQueue.data[idx].patientId, 
                    apptQueue.data[idx].doctorId, apptQueue.data[idx].date, apptQueue.data[idx].time, apptQueue.data[idx].status);
        }
        fclose(fq);
    }

    FILE *fh=fopen(EMERGENCY_FILE, "w");
    if(fh) {
        fprintf(fh, "%d\n", emergencyHeap.size);
        for(int i=0; i<emergencyHeap.size; i++) {
            fprintf(fh, "%d|%s|%s|%d\n", emergencyHeap.arr[i].patientId, emergencyHeap.arr[i].name, 
                    emergencyHeap.arr[i].condition, emergencyHeap.arr[i].priority);
        }
        fclose(fh);
    }

    FILE *fs=fopen(HISTORY_FILE, "w");
    if(fs) {
        fprintf(fs, "%d\n", historyStack.top);
        for(int i=0; i<=historyStack.top; i++) {
            fprintf(fs, "%d|%d|%s\n", historyStack.data[i].actionType, historyStack.data[i].entityId, historyStack.data[i].description);
        }
        fclose(fs);
    }
}

void loadOtherDataFromFile() {
    FILE *fq=fopen(APPT_FILE, "r");
    if(fq) {
        if(fscanf(fq, "%d|%d|%d|%d\n", &apptQueue.size, &apptQueue.front, &apptQueue.rear, &nextAppointmentId)==4) {
            for(int i=0; i<apptQueue.size; i++) {
                int idx=(apptQueue.front+i)%MAX_QUEUE;
                fscanf(fq, "%d|%d|%d|%[^|]|%[^|]|%[^\n]\n", &apptQueue.data[idx].appointmentId, &apptQueue.data[idx].patientId, 
                       &apptQueue.data[idx].doctorId, apptQueue.data[idx].date, apptQueue.data[idx].time, apptQueue.data[idx].status);
            }
        }
        fclose(fq);
    }

    FILE *fh=fopen(EMERGENCY_FILE, "r");
    if(fh) {
        if(fscanf(fh, "%d\n", &emergencyHeap.size)==1) {
            for(int i=0; i<emergencyHeap.size; i++) {
                fscanf(fh, "%d|%[^|]|%[^|]|%d\n", &emergencyHeap.arr[i].patientId, emergencyHeap.arr[i].name, 
                       emergencyHeap.arr[i].condition, &emergencyHeap.arr[i].priority);
            }
        }
        fclose(fh);
    }

    FILE *fs=fopen(HISTORY_FILE, "r");
    if(fs) {
        if(fscanf(fs, "%d\n", &historyStack.top)==1) {
            for(int i=0; i<=historyStack.top; i++) {
                fscanf(fs, "%d|%d|%[^\n]\n", &historyStack.data[i].actionType, &historyStack.data[i].entityId, historyStack.data[i].description);
            }
        }
        fclose(fs);
    }
}

void saveAllDataSecurely() {
    savePatientsToFile();     toggleFileEncryption(PATIENTS_FILE);
    saveDoctorsToFile();      toggleFileEncryption(DOCTORS_FILE);
    saveMedicinesToFile();    toggleFileEncryption(MEDICINES_FILE);
    saveDepartmentsToFile();  toggleFileEncryption(DEPT_FILE);
    saveOtherDataToFile(); 
    toggleFileEncryption(APPT_FILE);
    toggleFileEncryption(EMERGENCY_FILE);
    toggleFileEncryption(HISTORY_FILE);
}

void loadAllDataSecurely() {
    toggleFileEncryption(PATIENTS_FILE);  loadPatientsFromFile();    toggleFileEncryption(PATIENTS_FILE);
    toggleFileEncryption(DOCTORS_FILE);   loadDoctorsFromFile();     toggleFileEncryption(DOCTORS_FILE);
    toggleFileEncryption(MEDICINES_FILE); loadMedicinesFromFile();   toggleFileEncryption(MEDICINES_FILE);
    toggleFileEncryption(DEPT_FILE);      loadDepartmentsFromFile(); toggleFileEncryption(DEPT_FILE);

    toggleFileEncryption(APPT_FILE);
    toggleFileEncryption(EMERGENCY_FILE);
    toggleFileEncryption(HISTORY_FILE);
    
    loadOtherDataFromFile();

    toggleFileEncryption(APPT_FILE);
    toggleFileEncryption(EMERGENCY_FILE);
    toggleFileEncryption(HISTORY_FILE);
}

// SECTION 10: ANALYTICS & REPORTS
void generatePatientReport() {
    printf("\n  === PATIENT ANALYTICS REPORT ===\n\n");
    int admitted=0, outpatient=0, totalAge=0;
    Patient *curr=patientHead;
    while(curr) {
        if(curr->isAdmitted) admitted++;
        else outpatient++;
        totalAge+=curr->age;
        curr=curr->next;
    }
    printf("  Total Patients      : %d\n", patientCount);
    printf("  Admitted Patients   : %d", admitted);
    if(patientCount) printf(" (%.1f%%)", (admitted*100.0/patientCount));
    printf("\n  Outpatients         : %d", outpatient);
    if(patientCount) printf(" (%.1f%%)", (outpatient*100.0/patientCount));
    printf("\n");
    if(patientCount) printf("  Average Age         : %.1f\n", totalAge/(float)patientCount);
    printf("\n");
}

void generateDoctorReport() {
    printf("\n  === DOCTOR ANALYTICS REPORT ===\n\n");
    int available=0;
    Doctor *curr=doctorHead;
    while(curr) {
        if(curr->isAvailable) available++;
        curr=curr->next;
    }
    printf("  Total Doctors       : %d\n", doctorCount);
    printf("  Available Doctors   : %d", available);
    if(doctorCount) printf(" (%.1f%%)", (available*100.0/doctorCount));
    printf("\n  Busy Doctors        : %d", doctorCount-available);
    if(doctorCount) printf(" (%.1f%%)", ((doctorCount-available)*100.0/doctorCount));
    printf("\n\n");
}

void displayStatistics() {
    printf("\n  === COMPLETE SYSTEM STATISTICS ===\n\n");
    printf("  LINKED LISTS:\n");
    printf("    Total Patients   : %d\n", patientCount);
    printf("    Total Doctors    : %d\n", doctorCount);
    printf("    Total Medicines  : %d\n\n", medicineCount);
    printf("  QUEUE (FIFO):\n");
    printf("    Pending Appointments: %d/%d (%.1f%%)\n", apptQueue.size, MAX_QUEUE, 
           MAX_QUEUE ? (apptQueue.size*100.0/MAX_QUEUE) : 0);
    printf("    Total Processed  : %d\n\n", appointmentCount-apptQueue.size);
    printf("  MAX HEAP (Priority):\n");
    printf("    Emergency Patients: %d/%d\n\n", emergencyHeap.size, MAX_HEAP);
    printf("  STACK (LIFO):\n");
    printf("    History Entries  : %d/%d\n\n", historyStack.top+1, MAX_STACK);
}

void findDoctorWithMinPatients() {
    printf("\n  === DOCTOR WITH MINIMUM PATIENTS ===\n");
    if(!doctorHead) { printf("  NO DOCTORS.\n\n"); return; }
    
    Doctor *minDoctor=doctorHead;
    Doctor *curr=doctorHead;
    while(curr) {
        if(curr->patientCount<minDoctor->patientCount) minDoctor=curr;
        curr=curr->next;
    }
    
    printf("  Doctor: %s\n", minDoctor->name);
    printf("  ID: %d\n", minDoctor->id);
    printf("  Specialization: %s\n", minDoctor->specialization);
    printf("  Current Patients: %d\n\n", minDoctor->patientCount);
}

void findDoctorWithMaxPatients() {
    printf("\n  === DOCTOR WITH MAXIMUM PATIENTS ===\n");
    if(!doctorHead) { printf("  NO DOCTORS.\n\n"); return; }
    
    Doctor *maxDoctor=doctorHead;
    Doctor *curr=doctorHead;
    while(curr) {
        if(curr->patientCount>maxDoctor->patientCount) maxDoctor=curr;
        curr=curr->next;
    }
    
    printf("  Doctor: %s\n", maxDoctor->name);
    printf("  ID: %d\n", maxDoctor->id);
    printf("  Specialization: %s\n", maxDoctor->specialization);
    printf("  Current Patients: %d\n\n", maxDoctor->patientCount);
}

void findMostExpensiveMedicine() {
    printf("\n  === MOST EXPENSIVE MEDICINE ===\n");
    if(!medicineHead) { printf("  NO MEDICINES.\n\n"); return; }
    
    Medicine *expensive=medicineHead;
    Medicine *curr=medicineHead;
    while(curr) {
        if(curr->price>expensive->price) expensive=curr;
        curr=curr->next;
    }
    
    printf("  Medicine: %s\n", expensive->name);
    printf("  ID: %d\n", expensive->id);
    printf("  Price: %.2f\n", expensive->price);
    printf("  Quantity: %d units\n\n", expensive->quantity);
}

void findCheapestMedicine() {
    printf("\n  === CHEAPEST MEDICINE ===\n");
    if(!medicineHead) { printf("  NO MEDICINES.\n\n"); return; }
    
    Medicine *cheapest=medicineHead;
    Medicine *curr=medicineHead;
    while(curr) {
        if(curr->price<cheapest->price) cheapest=curr;
        curr=curr->next;
    }
    
    printf("  Medicine: %s\n", cheapest->name);
    printf("  ID: %d\n", cheapest->id);
    printf("  Price: %.2f\n", cheapest->price);
    printf("  Quantity: %d units\n\n", cheapest->quantity);
}

void calculateTotalMedicineValue() {
    printf("\n  === MEDICINE INVENTORY VALUE ANALYSIS ===\n");
    float totalValue=0;
    Medicine *curr=medicineHead;
    
    while(curr) {
        float itemValue=curr->price*curr->quantity;
        totalValue+=itemValue;
        curr=curr->next;
    }
    
    printf("  Total Medicine Items  : %d\n", medicineCount);
    printf("  Total Inventory Value : Rs. %.2f\n", totalValue);
    if(medicineCount) printf("  Average Item Value    : Rs. %.2f\n", totalValue/medicineCount);
    printf("\n");
}

void displayOldestPatients() {
    printf("\n  === PATIENTS BY AGE (Oldest First) ===\n");
    printf("  %-6s %-20s %-6s %-20s\n", "ID", "Name", "Age", "Disease");
    printf("  %s\n", "-----------------------------------");
    
    Patient *patients[100];
    int count=0;
    Patient *curr=patientHead;
    while(curr && count<100) {
        patients[count++]=curr;
        curr=curr->next;
    }
    
    for(int i=0; i<count-1; i++) {
        for(int j=i+1; j<count; j++) {
            if(patients[i]->age<patients[j]->age) {
                Patient *tmp=patients[i];
                patients[i]=patients[j];
                patients[j]=tmp;
            }
        }
    }
    
    for(int i=0; i<count && i<20; i++) {
        printf("  %-6d %-20s %-6d %-20s\n", patients[i]->id, patients[i]->name, 
               patients[i]->age, patients[i]->disease);
    }
    printf("\n");
}

void getAppointmentStatistics() {
    printf("\n  === APPOINTMENT QUEUE STATISTICS ===\n");
    printf("  Total Capacity       : %d\n", MAX_QUEUE);
    printf("  Current Appointments : %d\n", apptQueue.size);
    printf("  Processed Appointments: %d\n", appointmentCount-apptQueue.size);
    
    if(MAX_QUEUE) {
        float occupancy=(apptQueue.size*100.0)/MAX_QUEUE;
        printf("  Queue Occupancy      : %.1f%%\n", occupancy);
    }
    
    if(appointmentCount>0) {
        float processRate=((appointmentCount-apptQueue.size)*100.0)/appointmentCount;
        printf("  Processing Rate      : %.1f%%\n", processRate);
    }
    printf("\n");
}

void getEmergencyStatistics() {
    printf("\n  === EMERGENCY QUEUE STATISTICS ===\n");
    printf("  Total Capacity       : %d\n", MAX_HEAP);
    printf("  Current Emergencies  : %d\n", emergencyHeap.size);
    
    int critical=0, serious=0, normal=0;
    for(int i=0; i<emergencyHeap.size; i++) {
        if(emergencyHeap.arr[i].priority==3) critical++;
        else if(emergencyHeap.arr[i].priority==2) serious++;
        else normal++;
    }
    
    printf("  Critical Patients    : %d\n", critical);
    printf("  Serious Patients     : %d\n", serious);
    printf("  Normal Patients      : %d\n", normal);
    
    if(MAX_HEAP) {
        float occupancy=(emergencyHeap.size*100.0)/MAX_HEAP;
        printf("  Queue Occupancy      : %.1f%%\n", occupancy);
    }
    printf("\n");
}

void displayBloodGroupDistribution() {
    printf("\n  === BLOOD GROUP DISTRIBUTION ===\n");
    
    char bloodGroups[8][5]={"A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"};
    int count[8]={0};
    
    Patient *curr=patientHead;
    while(curr) {
        for(int i=0; i<8; i++) {
            if(strcmp(curr->bloodGroup, bloodGroups[i])==0) {
                count[i]++;
                break;
            }
        }
        curr=curr->next;
    }
    
    printf("  Blood Group | Count | Percentage\n");
    printf("  %s\n", "-------------------------------");
    for(int i=0; i<8; i++) {
        if(count[i]>0 && patientCount>0) {
            float percentage=(count[i]*100.0)/patientCount;
            printf("  %-11s | %-5d | %.1f%%\n", bloodGroups[i], count[i], percentage);
        }
    }
    printf("\n");
}

void getDiseaseDistribution() {
    printf("\n  === COMMON DISEASES IN HOSPITAL ===\n");
    printf("  Disease              | Count | Percentage\n");
    printf("  %s\n", "-------------------------------");
    
    struct Disease { char name[100]; int count; } diseases[50];
    int diseaseCount=0;
    
    Patient *curr=patientHead;
    while(curr) {
        int found=0;
        for(int i=0; i<diseaseCount; i++) {
            if(strcmp(diseases[i].name, curr->disease)==0) {
                diseases[i].count++;
                found=1;
                break;
            }
        }
        if(!found && diseaseCount<50) {
            strcpy(diseases[diseaseCount].name, curr->disease);
            diseases[diseaseCount].count=1;
            diseaseCount++;
        }
        curr=curr->next;
    }
    
    for(int i=0; i<diseaseCount; i++) {
        if(patientCount>0) {
            float percentage=(diseases[i].count*100.0)/patientCount;
            printf("  %-20s | %-5d | %.1f%%\n", diseases[i].name, diseases[i].count, percentage);
        }
    }
    printf("\n");
}

// SECTION 11: MENUS
void mainMenu() {
    printf("\n  ====================================================\n");
    printf("       SECURE HOSPITAL MANAGEMENT SYSTEM - MENU\n");
    printf("  ====================================================\n\n");
    printf("  PATIENT MANAGEMENT:\n");
    printf("  1. Add Patient         2. Delete Patient        3. Search by ID\n");
    printf("  4. Search by Name      5. Search by Disease     6. Update Patient\n");
    printf("  7. Admit Patient       8. Discharge Patient     9. View All\n");
    printf("  10. View Admitted Patients\n\n");
    printf("  DOCTOR MANAGEMENT:\n");
    printf("  11. Add Doctor         12. Search by Specialization  13. Toggle Availability\n");
    printf("  14. Delete Doctor      15. View All Doctors\n\n");
    printf("  APPOINTMENT MANAGEMENT (Queue - FIFO):\n");
    printf("  16. Book Appointment   17. Process Appointment  18. View Queue\n\n");
    printf("  EMERGENCY MANAGEMENT (Max Heap):\n");
    printf("  19. Register Emergency 20. Treat Next Patient   21. View Emergency Queue\n\n");
    printf("  DEPARTMENT MANAGEMENT (BST):\n");
    printf("  22. Add Department     23. Search Department    24. View All Departments\n\n");
    printf("  MEDICINE MANAGEMENT:\n");
    printf("  25. Add Medicine       26. View All Medicines   27. Check Low Stock\n");
    printf("  28. Update Stock       29. Delete Medicine\n\n");
    printf("  FILE, ANALYTICS & SECURITY:\n");
    printf("  30. Save All Data      31. Load All Data        32. View History (Stack)\n");
    printf("  33. Patient Report     34. Doctor Report        35. System Statistics\n");
    printf("  36. Extended Analytics Menu\n");
    printf("  37. Change System Password (SECURITY)\n");
    printf("  0. Exit Program\n\n");
    printf("  ENTER YOUR CHOICE: ");
}

void extendedMenu() {
    printf("\n  === EXTENDED ANALYTICS MENU ===\n");
    printf("  1. Doctor with Min Patients\n");
    printf("  2. Doctor with Max Patients\n");
    printf("  3. Most Expensive Medicine\n");
    printf("  4. Cheapest Medicine\n");
    printf("  5. Total Medicine Value\n");
    printf("  6. Oldest Patients List\n");
    printf("  7. Appointment Queue Stats\n");
    printf("  8. Emergency Queue Stats\n");
    printf("  9. Blood Group Distribution\n");
    printf("  10. Disease Distribution\n");
    printf("  0. Back to Main Menu\n\n");
    printf("  CHOICE: ");
    
    int choice;
    if(scanf("%d", &choice)!=1) {
        while(getchar()!='\n'); 
        return;
    }
    
    switch(choice) {
        case 1: findDoctorWithMinPatients(); break;
        case 2: findDoctorWithMaxPatients(); break;
        case 3: findMostExpensiveMedicine(); break;
        case 4: findCheapestMedicine(); break;
        case 5: calculateTotalMedicineValue(); break;
        case 6: displayOldestPatients(); break;
        case 7: getAppointmentStatistics(); break;
        case 8: getEmergencyStatistics(); break;
        case 9: displayBloodGroupDistribution(); break;
        case 10: getDiseaseDistribution(); break;
        case 0: break;
        default: printf("  INVALID CHOICE!\n\n");
    }
}