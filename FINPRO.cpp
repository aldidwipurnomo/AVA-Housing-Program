#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int ID,nilai;
	char nama[200];
	struct node *kiri,*kanan;
}*akar;

struct node* buatnode(int ID,int nilai,char nama[]){
	struct node* nodebaru = (struct node*)malloc(sizeof(struct node));
	nodebaru->ID = ID;
	nodebaru->nilai = nilai;
	strcpy(nodebaru->nama,nama);
	nodebaru->kiri = NULL;
	nodebaru->kanan = NULL;
	return nodebaru;
}

struct node* insert(struct node* akar,int ID,int nilai,char nama[],int tinggi){
	if(tinggi < 3){
		if(!akar){
			printf("\n\t--- PENAMBAHAN BERKAS KEPEMILIKAN RUMAH BERHASIL ---\n\t        SEMOGA HARI ANDA SELALU BAHAGIA\n");
			fflush(stdin);
			getchar();
			return buatnode(ID,nilai,nama);
		}
		while(tinggi < 3){
			if(ID < akar->ID){
				akar->kiri = insert(akar->kiri,ID,nilai,nama,tinggi+1);
			}
			else if(ID > akar->ID){
				akar->kanan = insert(akar->kanan,ID,nilai,nama,tinggi+1);
			}
			break;
		}
	}
	else{
		printf("\n\t--- Kapasitas Maksimum Blok Terpenuhi ---\n\t       Harap Menempati Rumah yang lain\n");
		fflush(stdin);
		getchar();
	}
	return akar;
}

struct node* carinode(struct node* akar, int id)
{
    if(akar==NULL || akar->ID==id){
        return akar;
    }else if(id>akar->ID){ 
        return carinode(akar->kanan, id);
    }else{ 
        return carinode(akar->kiri,id);
    }
}

bool ceknode(struct node* Node, int key)
{
    if (Node == NULL)
        return false;
 
    if (Node->ID == key)
        return true;
 
    /* then recur on left sutree */
    bool res1 = ceknode(Node->kiri, key);
    // node found, no need to look further
    if(res1) return true;
 
    /* node is not found in left,
    so recur on right subtree */
    bool res2 = ceknode(Node->kanan, key);
 
    return res2;
}

void update(struct node* akar,char namabaru[],int nilaibaru){
	if(akar!=NULL){
    strcpy(akar->nama,namabaru);
		akar->nilai=nilaibaru;
	}
}

struct node* minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->kiri != NULL)
        current = current->kiri;
 
    return current;
}

struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->ID)
        root->kiri = deleteNode(root->kiri, key);
 
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->ID)
        root->kanan = deleteNode(root->kanan, key);
 
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->kiri == NULL) {
            struct node* temp = root->kanan;
            free(root);
            return temp;
        }
        else if (root->kanan == NULL) {
            struct node* temp = root->kiri;
            free(root);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->kanan);
 
        // Copy the inorder
        // successor's content to this node
        root->ID = temp->ID;
 
        // Delete the inorder successor
        root->kanan = deleteNode(root->kanan, temp->ID);
    }
    return root;
}

void Postorder(struct node* node)//Given a binary tree, print its nodes in Postorder
{
    if (node == NULL)
        return;
    Postorder(node->kiri);// first recur on left subtree
    Postorder(node->kanan);// then recur on right subtree
    printf("\t- E%d	%s			[	+62 %d	]\n", node->ID,node->nama,node->nilai);// now deal with the node
}
 

void Inorder(struct node* node)//Given a binary tree, print its nodes in inorder
{
    if (node == NULL)
        return;
    Inorder(node->kiri);//first recur on left child
    printf("\t- E%d	%s			[	+62 %d	]\n", node->ID,node->nama,node->nilai);//then print the data of node
    Inorder(node->kanan);//now recur on right child
}
 
void Preorder(struct node* node)//Given a binary tree, print its nodes in preorder
{
    if (node == NULL)
        return;
    printf("\t- E%d	%s			[	+62 %d	]\n", node->ID,node->nama,node->nilai);//first print data of node
    Preorder(node->kiri);//then recur on left sutree
    Preorder(node->kanan);//now recur on right subtree
}

//chalange
struct node* printbst(struct node* akar,int ID){
	if(akar != NULL){
		printf("\n\t       E%d\n",akar->ID);
		if(akar->kanan != NULL && akar->kiri != NULL){
			printf("\t   /	    \\\n");
			printf("\t E%d	    E%d\n",akar->kiri->ID,akar->kanan->ID);
			if(akar->kiri->kiri == NULL && akar->kiri->kanan == NULL && akar->kanan->kiri != NULL && akar->kanan->kanan == NULL){
				printf("\t      \t   /\n");
				printf("                 E%d\n\n",akar->kanan->kiri->ID);
			}
			if(akar->kiri->kiri == NULL && akar->kiri->kanan == NULL && akar->kanan->kiri == NULL && akar->kanan->kanan != NULL){
				printf("\t      \t       \\\n");
				printf("                      E%d\n\n",akar->kanan->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan == NULL && akar->kanan->kiri == NULL && akar->kanan->kanan == NULL){
				printf("\t/\n");
				printf("     E%d\n\n",akar->kiri->kiri->ID);
			}
			if(akar->kiri->kiri == NULL && akar->kiri->kanan != NULL && akar->kanan->kiri == NULL && akar->kanan->kanan == NULL){
				printf("\t    \\\t\n");
				printf("            E%d\n\n",akar->kiri->kanan->ID);
			}
			if(akar->kiri->kiri == NULL && akar->kiri->kanan == NULL && akar->kanan->kiri != NULL && akar->kanan->kanan != NULL){
				printf("\t      \t   /   \\\n");
				printf("                 E%d  E%d\n\n",akar->kanan->kiri->ID,akar->kanan->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan != NULL && akar->kanan->kiri == NULL && akar->kanan->kanan == NULL){
				printf("\t/   \\\t\n");
				printf("     E%d    E%d\n\n",akar->kiri->kiri->ID,akar->kiri->kanan->ID);
			}
			if(akar->kiri->kiri == NULL && akar->kiri->kanan != NULL && akar->kanan->kiri != NULL && akar->kanan->kanan != NULL){
				printf("\t    \\\t   /   \\\n");
				printf("            E%d  E%d  E%d\n\n",akar->kiri->kanan->ID,akar->kanan->kiri->ID,akar->kanan->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan == NULL && akar->kanan->kiri != NULL && akar->kanan->kanan != NULL){
				printf("\t/     \t   /   \\\n");
				printf("     E%d         E%d  E%d\n\n",akar->kiri->kiri->ID,akar->kanan->kiri->ID,akar->kanan->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan != NULL && akar->kanan->kiri == NULL && akar->kanan->kanan != NULL){
				printf("\t/   \\\t       \\\n");
				printf("     E%d    E%d       E%d\n\n",akar->kiri->kiri->ID,akar->kiri->kanan->ID,akar->kanan->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan != NULL && akar->kanan->kiri != NULL && akar->kanan->kanan == NULL){
				printf("\t/   \\\t   /     \n");
				printf("     E%d    E%d  E%d     \n\n",akar->kiri->kiri->ID,akar->kiri->kanan->ID,akar->kanan->kiri->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan != NULL && akar->kanan->kiri != NULL && akar->kanan->kanan != NULL){
				printf("\t/   \\\t   /   \\\n");
				printf("     E%d    E%d  E%d  E%d\n\n",akar->kiri->kiri->ID,akar->kiri->kanan->ID,akar->kanan->kiri->ID,akar->kanan->kanan->ID);
			}
		}
		if(akar->kiri != NULL){
			if(akar->kanan == NULL){
				printf("\t   /\n");
				printf("\t E%d\n",akar->kiri->ID);
			}
		}
		if(akar->kanan != NULL){
			if(akar->kiri == NULL){
				printf("\t    	    \\\n");
				printf("\t    	    E%d\n",akar->kanan->ID);
			}
		}
		if(akar->kiri == NULL && akar->kanan != NULL){
			if(akar->kanan->kiri != NULL && akar->kanan->kanan == NULL){
				printf("\t      \t   /\n");
				printf("                 E%d\n\n",akar->kanan->kiri->ID);
			}
			if(akar->kanan->kiri == NULL && akar->kanan->kanan != NULL){
				printf("\t      \t       \\\n");
				printf("                      E%d\n\n",akar->kanan->kanan->ID);
			}
			if(akar->kanan->kiri != NULL && akar->kanan->kanan != NULL){
				printf("\t      \t   /   \\\n");
				printf("                 E%d  E%d\n\n",akar->kanan->kiri->ID,akar->kanan->kanan->ID);
			}
		}
		if(akar->kiri != NULL && akar->kanan == NULL){
			if(akar->kiri->kiri != NULL && akar->kiri->kanan == NULL){
				printf("\t/\n");
				printf("     E%d\n\n",akar->kiri->kiri->ID);
			}
			if(akar->kiri->kiri == NULL && akar->kiri->kanan != NULL){
				printf("\t    \\\t\n");
				printf("            E%d\n\n",akar->kiri->kanan->ID);
			}
			if(akar->kiri->kiri != NULL && akar->kiri->kanan != NULL){
				printf("\t/   \\\t\n");
				printf("     E%d    E%d\n\n",akar->kiri->kiri->ID,akar->kiri->kanan->ID);
			}
		}
	}
	else printf("\n\t--- MOHON MAAF, TIDAK ADA SATUPUN RUMAH YANG BERPENGHUNI ---\n");
}

void menu(){
	printf("\n\t\t\t\t   Aplikasi Perumahan AVA\n");
	printf("\t\t\t  ========================================== \n\n");
	printf("  Selamat datang di perumahan AVA. Perumahan yang di desain kekinian dengan konsep komputerisasi.\n     Dimana penentuan kepemilikan rumah berdasarkan nomor rumah yang diinginkan pemilik rumah.\n");
	printf("\n\n\n DAFTAR MENU APLIKASI PERUMAHAN 'AVA'\n -------------------------------\n");
	printf("\n 1. Pendaftaran Penghuni Baru di Perumahan AVA\n");
	printf(" 2. Perbaharuan Data Kepemilikan Rumah di Perumahan AVA\n");
	printf(" 3. Tampilan Data Pemilik Rumah di Perumahan AVA\n");
	printf(" 4. Pencarian Rumah Berdasarkan Nomor Telepon\n");
	printf(" 5. Denah Perumahan AVA\n");
	printf(" 6. Pencabutan Berkas Kepemilikan Rumah di Perumahan AVA\n");
	printf(" 7. Keluar\n");
	printf("\n >> Masukan Pilihan Anda : ");
}

int main(){
	int select;
	char nama[200],E;
	int nilai,ID;
	struct node* akar=NULL;
	menu:
	
	menu();
	scanf("%d",&select);
	fflush(stdin);
	if(select == 1){
		inputid:
		printf("\n\tMasukan Nomor Rumah E[1-9][0-9]: ");
		scanf("%c%d",&E,&ID);
		if(E != 'E' || ID < 10){
			printf("\n\t\tINPUTAN NOMOR YANG DIBERIKAN SALAH\n\t   HARAP MEMASUKAN KEMBALI SESUAI DENGAN KETENTUAN\n");
			fflush(stdin);
			getchar();
			system("cls");
			printbst(akar,ID);
			menu();
			printf("1\n");
			goto inputid;
		}
		if(ceknode(akar,ID)){
			printf("\n      --- \tMOHON MAAF, NOMOR RUMAH YANG ANDA GUNAKAN SAMA\t\t---\n\t    SILAKAN MEMASUKAN KEMBALI NOMOR RUMAH YANG ANDA INGINKAN");
			fflush(stdin);
			getchar();
			system("cls");
			goto menu;
		}
		printf("\n\tMasukan Nama Pemilik Rumah: ");
		scanf("\n%[^\n]",&nama);
		inputnilai:
		printf("\n\tMasukan Nomor Telpon  [8 digit]: +62 ");
		scanf("%d",&nilai);
		if(nilai < 10000000 || nilai > 99999999){
			printf("\n\t\t Jumlah angka nomor telpon harus 8 digit\n");
			fflush(stdin);
			getchar();
			system("cls");
			printbst(akar,ID);
			menu();
			printf("1\n");
			printf("\n\tMasukan Nomor Rumah E[1-9][0-9]: %c%d\n",E,ID);
			printf("\n\tMasukan Nama Pemilik Rumah: %s\n",nama);
			goto inputnilai;
		}
		akar = insert(akar,ID,nilai,nama,0);
		
		system("cls");
		goto menu;		
	}
	else if(select == 2){
		if(akar == NULL){
			printf("\n\t--- There is no data in the tree ---\n");
			fflush(stdin);
			getchar();
			system("cls");
			goto menu;
		}
		printf("\n\tMasukan Nomor Rumah E[1-9][0-9]: ");
		scanf("%c%d",&E,&ID);
		struct node *temp = carinode(akar,ID);
		if(temp == NULL  || E != 'E' || ID < 10){
			printf("\n\t--- \t   NOMOR RUMAH TIDAK DITEMUKAN \t\t---\n              SILAKAN MASUKAN NOMOR RUMAH YANG SESUAI\n");
			fflush(stdin);
			getchar();
			system("cls");
			goto menu;
		}
		else{
			inputnamaup:
			printf("\n\tMasukan Nama Pemilik Rumah: ");
			scanf("\n%[^\n]",&nama);
			inputnilai2:
			printf("\n\tMasukan Nomor Telpon  [8 digit]: +62 ");
			scanf("%d",&nilai);
			if(nilai < 10000000 || nilai > 99999999){
				printf("\n\t\t Jumlah angka nomor telpon harus 8 digit\n");
				fflush(stdin);
				getchar();
				system("cls");
				printbst(akar,ID);
				menu();
				printf("2\n");
				printf("\n\tMasukan Nomor Rumah E[1-9][0-9]: %c%d\n",E,ID);
				printf("\n\tMasukan Nama Pemilik Rumah: %s\n",nama);
			goto inputnilai2;
		}
			temp = carinode(akar,ID);
			printf("\n\t --- Pembeharuan Data Berhasil ---\n");
			fflush(stdin);
			getchar();
		}
		system("cls");
		goto menu;
	}
	else if(select == 3){
		fflush(stdin);
		if(akar == NULL){
			printf("\n\t--- MOHON MAAF, TIDAK ADA SATUPUN RUMAH YANG BERPENGHUNI ---\n");
		}
		else{
			printf("\nPreorder	: \n");
			Preorder(akar);
			printf("\nInorder	: \n");
			Inorder(akar);
			printf("\nPostorder	: \n");
			Postorder(akar);
		}
		getchar();
		system("cls");
		goto menu;
	}
	else if(select == 4){
		printf(" Masukan Nomor Telepon Pemilik Rumah : +62 ");
		getchar();
		system("cls");
		goto menu;
	}
	else if(select == 5){
		printbst(akar,ID);
		getchar();
		system("cls");
		goto menu;
		
	}
	else if(select == 6){
		if(akar == NULL){
			printf("\n\t--- MOHON MAAF, TIDAK ADA SATUPUN RUMAH YANG BERPENGHUNI ---\n");
			fflush(stdin);
			getchar();
			system("cls");
			goto menu;
		}
		printf("\n\tInput Student ID E[1-9][0-9]: ");
		scanf("%c%d",&E,&ID);
		if(E != 'E' || !ceknode(akar,ID) || ID < 10){
			printf("\n\t--- \t   NOMOR RUMAH TIDAK DITEMUKAN \t\t---\n              SILAKAN MASUKAN NOMOR RUMAH YANG SESUAI\n");
			fflush(stdin);
			getchar();
			system("cls");
			goto menu;
		}
		akar = deleteNode(akar,ID);
		printf("\n\t--- PENCABUTAN BERKAS KEPEMILIKAN RUMAH BERHASIL ---\n\t        SAMPAI BERTEMU LAGI\n");
		fflush(stdin);
		getchar();
		system("cls");
		goto menu;
	}
	else if(select == 7){
		printf("\n\t TERIMA KASIH ATAS KUNJUNGAN ANDA DI APLIKASI PERUMAHAN 'AVA'!\n");
		getchar();
		exit(0);
		return 0;
	}
	else{
		printf("\n\tKESALAHAN INPUT, DIHARAPKAN UNTUK MEMASUKAN INPUT KEMBALI!\n");
		getchar();
		system("cls");
		goto menu;
	}
	return 0;
}
