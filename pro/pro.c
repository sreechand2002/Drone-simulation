#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
int max=9,j=0;
struct Drone
{
    int dr_no;
    float max_distance,load_capacity;
    float high_distance,high_weight;
    char dr_name[20];
};
struct Drone dr[20];
struct Delivery
{
    int drone_id;
    char drone_name[20];
    float max_distance1,load_capacity1,load_delivered,dis;
    float src_x,src_y;
    float des_x,des_y;
};
struct Delivery d[100];

void setcolor(int c)
{
        WORD wcolor;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
        {
            wcolor = (csbi.wAttributes & 0xF0) + (c & 0x0F);
            SetConsoleTextAttribute(hStdOut,wcolor);
        }
}
void input()
{
    int no,i,flag=0;
    printf("\nEnter the drone no:");
    scanf("%d",&no);
    for(i=0;i<max;i++)
     {
        if(no==dr[i].dr_no)
        {
            printf("\nEnter drone name:");
            scanf("%s",&dr[i].dr_name);
            printf("Enter the max distance:");
            scanf("%f",&dr[i].max_distance);
            printf("Enter the max capacity:");
            scanf("%f",&dr[i].load_capacity);
            flag=1;
        }
     }
     ++max;
     if(flag==0)
     {
        dr[max].dr_no = no;
        printf("\nEnter drone name:");
        scanf("%s",&dr[max].dr_name);
        printf("Enter the max distance:");
        scanf("%f",&dr[max].max_distance);
        printf("Enter the max capacity:");
        scanf("%f",&dr[max].load_capacity);
     }
}

void search()
{
    char name[20];
    int i,j,flag=0;
    printf("Enter the drone name: ");
    scanf("%s",&name);
    for(i=0;i<=max;i++)
    {
        if(strcmp(name,dr[i].dr_name)==0)
        {
            printf("\n Drone no:%d",dr[i].dr_no);
            printf("\n Drone name:%s",dr[i].dr_name);
            printf("\n Maximum distance:%.2f",dr[i].max_distance);
            printf("\n Maximum capacity:%.2f",dr[i].load_capacity);
            printf("\n Highest distance:%.2f",dr[i].high_distance);
            printf("\n Highest weight:%.2f\n",dr[i].high_weight);
            flag=1;
        }
        if(strcmp(name,"all") == 0)
        {
            for(j=0;j<=max;j++)
            {
                printf("\n Drone no:%d",dr[j].dr_no);
                printf("\n Drone name:%s",dr[j].dr_name);
                printf("\n Maximum distance:%.2f",dr[j].max_distance);
                printf("\n Maximum capacity:%.2f",dr[j].load_capacity);
                printf("\n Highest distance:%.2f",dr[j].high_distance);
                printf("\n Highest weight:%.2f\n",dr[j].high_weight);
            }
            flag=1;break;
        }
    }
    if(flag==0)
    printf("\n No drones with such name found\n");
}

void simulation()
{
    float x1,y1,x2,y2,weight,distance;
    int i,k,flag=0;
    char ch,ch1;
    label:
    system("CLS");
    printf("Enter the co-ordinates of the warehouse X and Y respectively:");
    scanf("%f %f",&x1,&y1);
    printf("Enter the co-ordinates of the destination X and Y respectively:");
    scanf("%f %f",&x2,&y2);
    printf("Enter the weight to be delivered:");
    scanf("%f",&weight);
    if((x1<0 || x1>100) || (y1<0 || y1>100 ))
    {
        printf("%.2f %.2f (warehouse)out of range please enter correct value",x1,y1);
        Sleep(3000);
        goto label;
    }
    if((x2<-100 || x2>100) || (y2<-100 || y2>100 ))
    {
        printf("%.2f %.2f (destination)out of range please enter correct value",x2,y2);
        sleep(3000);
        goto label;
    }
    if(weight <= 0 || weight >=200)
    {
        printf("%.2f  (weight)out of range please enter correct value",weight);
        sleep(3000);
        goto label;
    }
    distance = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    for(i=0;i<max;i++)
    {
        if(distance<=dr[i].max_distance && weight<=dr[i].load_capacity)
        {
            d[j].drone_id = dr[i].dr_no;
            strcpy(d[j].drone_name,dr[i].dr_name);
            d[j].src_x=x1;
            d[j].src_y=y1;
            d[j].des_x=x2;
            d[j].des_y=y2;
            d[j].max_distance1 = dr[i].max_distance;
            d[j].load_capacity1 = dr[i].load_capacity;
            d[j].load_delivered = weight;
            d[j].dis = distance;
            if(distance > dr[i].high_distance)
            {
                printf("\n New distance is greater than the previous high , enter y to accept changes:");
                scanf(" %c",&ch);
                if(ch=='y')
                    dr[i].high_distance  = distance;
            }
            if(weight > dr[i].high_weight)
            {
                printf("\n New weight is greater than the previous high , enter y to accept changes:");
                scanf(" %c",&ch1);
                if(ch1=='y')
                    dr[i].high_weight  = weight;
            }
            setcolor(3);
            printf("\n Simulation result \n");
            setcolor(20);
            printf("\nDrone information\n");
            printf("\nDrone number\t\t\t%d\n",dr[i].dr_no);
            printf("Drone name\t\t\t%s\n",dr[i].dr_name);
            printf("Maximum distance\t\t%.2f\n",dr[i].max_distance);
            printf("Load capacity\t\t\t%.2f\n",dr[i].load_capacity);
            printf("Highest delivery distance\t%.2f\n",dr[i].high_distance);
            printf("Highest delivery load\t\t%.2f\n",dr[i].high_weight);
            setcolor(1);
            printf("\nTest Conditions\n");
            printf("Source location (x1,y1)\t\t%.2f %.2f\n",x1,y1);
            printf("Destination location (x1,y1)\t%.2f %.2f\n",x2,y2);
            printf("Weight Delivered\t\t%.2f\n",weight);
            setcolor(2);
            printf("\nSimulation conditions\n");
            printf("Distance of delivery\t\t%.2f\n",distance);
            for(k=i+1;k<max;k++)
            {
                if(distance<=dr[k].max_distance && weight<=dr[k].load_capacity)
                   { printf("Possible other drones\t\tY\n");flag=1;break;}
            }
            if(flag==0)
            printf("Possible other drones\t\tN");
            j++;
            break;
        }
    }

}


void display_result()
{
    char name[20];
    int i,k;
    printf("enter drone name:");
    scanf("%s",name);
    for(i=0;i<j;i++)
    {
        if(strcmp(d[i].drone_name,name) == 0)
        {
            printf("\n Simulation result \n");
            printf("\nDrone information\n");
            printf("Drone number\t\t%d\n",d[i].drone_id);
            printf("Drone name\t\t%s\n",d[i].drone_name);
            printf("Maximum distance\t\t%.2f\n",d[i].max_distance1);
            printf("Load capacity\t\t%.2f\n",d[i].load_capacity1);
            printf("Highest delivery distance\t\t%.2f\n",d[i].max_distance1);
            printf("Highest delivery load\t\t%.2f\n",d[i].load_capacity1);
            printf("Test Conditions\n");
            printf("Source location (x1,y1)\t\t%.2f %.2f\n",d[i].src_x,d[i].src_y);
            printf("Destination location (x1,y1)\t\t%.2f %.2f\n",d[i].des_x,d[i].des_y);
            printf("Weight Delivered\t\t%.2f\n",d[i].load_delivered);
            printf("Simulation conditions\n");
            printf("Distance of delivery\t\t%.2f\n",d[i].dis);
        }
        if(strcmp(name,"all")==0)
        {
            for(k=0;k<j;k++)
            {
                printf("\n Simulation result \n");
                printf("\nDrone information\n");
                printf("Drone number\t\t%d\n",d[k].drone_id);
                printf("Drone name\t\t%s\n",d[k].drone_name);
                printf("Maximum distance\t\t%.2f\n",d[k].max_distance1);
                printf("Load capacity\t\t%.2f\n",d[k].load_capacity1);
                printf("Highest delivery distance\t\t%.2f\n",d[k].max_distance1);
                printf("Highest delivery load\t\t%.2f\n",d[k].load_capacity1);
                printf("Test Conditions\n");
                printf("Source location (x1,y1)\t\t%.2f %.2f\n",d[k].src_x,d[k].src_y);
                printf("Destination location (x1,y1)\t\t%.2f %.2f\n",d[k].des_x,d[k].des_y);
                printf("Weight Delivered\t\t%.2f\n",d[k].load_delivered);
                printf("Simulation conditions\n");
                printf("Distance of delivery\t\t%.2f\n",d[k].dis);
            }
            break;
        }

    }

}


void winner()
{
    int i,pos1,pos2;
    float dis=0,wei=0;
    for(i=0;i<max;i++)
    {
        if(dr[i].high_distance >= dis)
        {
            dis = dr[i].high_distance;
            pos1=i;
        }
        if(dr[i].high_weight >= wei)
        {
            wei = dr[i].high_weight;
            pos2=i;
        }
    }
    printf("\n winner in distance = %s",dr[pos1].dr_name);
    printf("\n winner in weight = %s",dr[pos2].dr_name);
}


void save_info()
{
    int i;
    FILE *fp;
    fp = fopen("Drone.txt","w");
    for(i=0;i<10;i++)
        fprintf(fp,"%d %s %.2f %.2f %.2f %.2f\n",dr[i].dr_no,dr[i].dr_name,dr[i].max_distance,dr[i].load_capacity,dr[i].high_distance,dr[i].high_weight);
    fclose(fp);

}

void save_res()
{
    int i;
    FILE *fp;
    fp = fopen("Results.txt","a");
    for(i=0;i<j;i++)
        fprintf(fp,"%s %.2f %.2f %.2f %.2f %.2f\n",d[i].drone_name,d[i].src_x,d[i].src_y,d[i].des_x,d[i].des_y,d[i].dis);
    fclose(fp);
}
void main()
{
    int n,i=0;
    FILE *fp;
    fp = fopen("Drone.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %f %f %f %f",&dr[i].dr_no,&dr[i].dr_name,&dr[i].max_distance,&dr[i].load_capacity,&dr[i].high_distance,&dr[i].high_weight);
        i++;
    }
    fclose(fp);
    do
    {
        setcolor(15);
        printf("\n 1. Input/update drone information");
        printf("\n 2. Search a drone");
        printf("\n 3. Simulate a drone delivery scenario");
        printf("\n 4. Display simulation result");
        printf("\n 5. Display winner drone");
        printf("\n 6. Save drone information");
        printf("\n 7. Save all results");
        printf("\n 8. Exit\n");
        scanf("%d",&n);
        system("CLS");
        switch(n)
        {
            case 1:
                    input();
                    break;
            case 2:
                    search();
                    break;
            case 3:
                    simulation();
                    break;
            case 4:
                    display_result();
                    break;
            case 5:
                    winner();
                    break;
            case 6:
                    save_info();
                    break;
            case 7:
                    save_res();
                    break;
            case 8:
                    exit(0);
        }
    }while(n!=8);
}
