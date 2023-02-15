#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RECORDS 24
#define DAYS 365

char sensor_arr[4][20] = {"temperature","sound","humidity","wind"};			//Types of sensor(Please enter this Sensor types only)

typedef struct sensor_tag
{
	int sensor_id;
	char sensor_type[20];
	char sensor_loc[20];
	int duration;               //Duration in mins
	int station_dist;
	struct sensor_tag* next;
	struct sensor_tag* prev;  
}sensor_node;

typedef struct date_tag
{
	int day;
	int month;
	int year;
	float Time[RECORDS];			 
	float data[RECORDS];			
}Date;

typedef struct record_tag
{
	int sensor_ID;
	char sensor_type[20];
	Date d[DAYS];
	struct record_tag* next;
	struct record_tag* prev;		
}record;

typedef struct AQI_record_tag           
{
	int PM10;
	int PM10_time;         //time interval in hours
	int PM25;
	int PM25_time;
	int Ozone_level;
	int OL_time;
	
	int day;
	int month;
	int year;
	
	int final_AQI;	
	
}AQI_info; 

 typedef struct Air_Quality_Index
{
	int sensor_id;
	AQI_info A[DAYS];
	char sensor_loc[20];
	struct Air_Quality_Index* next;
	struct Air_Quality_Index* prev;
}AQI;



void create_sensor_list(sensor_node** head_ptr)
{
	int flag=1;
	sensor_node *nptr,*lptr;
	lptr= (*head_ptr);
	
	while(flag!=0)
	{
		nptr = (sensor_node*)malloc(sizeof(sensor_node));
		
		printf("\nEnter sensor id: ");		
		scanf("%d",&nptr->sensor_id);
		
		printf("Enter sensor type: ");
		scanf("%s",nptr->sensor_type);
		
		printf("Enter sensor location: ");
		scanf("%s",nptr->sensor_loc);
		
		printf("Enter time duration(in mins): ");
		scanf("%d",&nptr->duration);
		
		if(lptr==NULL)
		{
			nptr->station_dist = 0;
			nptr->prev = NULL;
			nptr->next = NULL;
			lptr = nptr;
			*head_ptr=lptr;
		}
		else
		{
			printf("Enter previous station dist(in KM): ");
			scanf("%d",&nptr->station_dist);
			
			nptr->prev = lptr;
			lptr->next = nptr;
			nptr->next = NULL;
			lptr = nptr;		
		}
		printf("\nTo create new sensor node enter 1 else 0: ");
		scanf("%d",&flag);
	}
	
}

record* central_repository(sensor_node* head_ptr, record* repo)
{																			
	int i,j;
	sensor_node* lptr = head_ptr;
	record* nptr;
	record* temp_repo = repo;
	printf("Enter Data for central repository\n");
	while(lptr != NULL)
	{
		nptr = (record*)malloc(sizeof(record));
		nptr->sensor_ID = lptr->sensor_id;
		strcpy(nptr->sensor_type,lptr->sensor_type);
		printf("Sensor id: %d\n",nptr->sensor_ID);
		printf("Sensor type: %s\n",nptr->sensor_type);
		for(i=0;i<DAYS;i++)
		{
			printf("Enter date: ");
			scanf("%d %d %d",&nptr->d[i].day,&nptr->d[i].month,&nptr->d[i].year);
			
			printf("Enter time and data\n");
			for(j=0;j<RECORDS;j++)
			{
				scanf("%f",&nptr->d[i].Time[j]);			
				scanf("%f",&nptr->d[i].data[j]);
			}
		}
		if(temp_repo == NULL)
		{
			nptr->next = NULL;
			nptr->prev = NULL;
			temp_repo = nptr;
			repo = temp_repo;
		}
		else
		{
			nptr->prev = temp_repo;
			temp_repo->next = nptr;
			nptr->next = NULL;
			temp_repo = nptr;	
		}
		lptr = lptr->next;
		
	}
	return repo;
}


						
sensor_node* install_new_sensor(sensor_node* head_ptr)				
{
	sensor_node *new_node,*check_node;

	sensor_node *next_ptr = head_ptr->next;
	sensor_node *curr_ptr = head_ptr;
	
	//A part
	while(next_ptr != NULL)					
	{
		if(next_ptr->station_dist >10)
		{
			printf("\nAdd new sensor as the dist is greater than 10");
			new_node = (sensor_node*)malloc(sizeof(sensor_node));
			
			printf("\nEnter sensor id: ");				
			scanf("%d",&new_node->sensor_id);
		
			printf("Enter sensor type: ");
			scanf("%s",new_node->sensor_type);
		
			printf("Enter sensor location: ");
			scanf("%s",new_node->sensor_loc);
		
			printf("Enter time duration(in mins): ");
			scanf("%d",&new_node->duration);
		
		
			printf("Enter previous station dist(in KM): ");
			scanf("%d",&new_node->station_dist);
			while(new_node->station_dist > next_ptr->station_dist)
			{
				printf("Please enter dist less than dist of next sensor\n");
				scanf("%d",&new_node->station_dist);					
			}
			next_ptr->station_dist -= new_node->station_dist;
			
			new_node->prev = curr_ptr;
			curr_ptr->next = new_node;
			new_node->next = next_ptr;
			next_ptr->prev = new_node;
				
		}
		else
		{
			curr_ptr = next_ptr;
			next_ptr = next_ptr->next;
			
		}	
	}
	
	//B part
	int i,found=0;
	for(i=0;i<4;i++)
	{
		check_node = head_ptr;
		while(check_node->next != NULL && (found==0))
		{
			if(strcmp(check_node->sensor_type,sensor_arr[i])==0)
			{
				found=1;
			}
			else
			{
				check_node = check_node->next;
			}
		}
		if(strcmp(check_node->sensor_type,sensor_arr[i])==0 && (found==0))			//condition to check last node
		{
			found=1;
		}
		if(found==0)
		{
			printf("\nNo sensor found of type %s\n",sensor_arr[i]);
			printf("Adding sensor......");
			new_node = (sensor_node*)malloc(sizeof(sensor_node));
			
			printf("\nEnter sensor id: ");					
			scanf("%d",&new_node->sensor_id);
		
			strcpy(new_node->sensor_type,sensor_arr[i]);
			printf("sensor type: %s",new_node->sensor_type);
		
			printf("\nEnter sensor location: ");
			scanf("%s",new_node->sensor_loc);
		
			printf("Enter time duration(in mins): ");
			scanf("%d",&new_node->duration);
		
		
			printf("Enter previous station dist(in KM): ");
			scanf("%d",&new_node->station_dist);
			
			new_node->prev = check_node;
			check_node->next = new_node;
			new_node->next = NULL;			
		}
		
	}
	return head_ptr;
	
}


void idle_sensors(record** repo_ptr)
{
	int gap,i,flag=1;
	record* check = *repo_ptr;
	record* temp = NULL;
	record* prev_ptr = NULL;
	while(check != NULL)
	{
		for(i=0;i<DAYS-1 && (flag==1);i++)
		{
			gap = check->d[i+1].month - check->d[i].month;			//assume d[i+1].month > d[i].month
			if(gap > 2)
			{
				printf("Sensor id %d is idle for more than 2 months\n",check->sensor_ID);
				temp = check;
				if(check == (*repo_ptr))
				{
					check = check->next;
					*repo_ptr = check;
					check->prev = NULL;
					free(temp);
					temp=NULL;
					flag=0;
				}
				else if(check->next == NULL)
				{
					prev_ptr = check->prev;
					check = NULL;
					prev_ptr->next = NULL;
					free(temp);
					temp = NULL;
					flag=0;
				}
				else
				{
					prev_ptr = check->prev;
					check = check->next;
					prev_ptr->next = check;
					check->prev = prev_ptr;
					free(temp);
					temp = NULL;
					flag=0;					
				}
			}
		}
		if(flag==1)
		{
			check = check->next;
		}
	}
}


void retrieve_info(record* repo)
{
	int i=0,j,info,day2,day3,month2,month3,year2,year3,found=0;
	float time2;
	char type[20];
	record* retrieve = repo;
	printf("Enter Method\n");
	printf("press 1 if depending on sensor type (retrieves till date data)\n");
	printf("press 2 if depending on specified date for specific sensor type\n");
	printf("press 31 if depending on specific time interval for specific sensor type and for specified date (single day)\n");
	printf("press 32 if depending on specific time interval for specific sensor type and for specified date range (multiple dates)\n");
	scanf("%d",&info);
	switch(info)
	{
		case 1:
			{
				printf("Enter sensor type: ");
				scanf("%s",type);
				printf("Enter date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				while(strcmp(retrieve->sensor_type,type) !=0)
				{
					retrieve= retrieve->next;
				}
				while(found==0 && i<DAYS)
				{
					for(j=0;j<RECORDS;j++)
					{
						printf("%f ",retrieve->d[i].data[j]);							
					}
					printf("\n");
					if((year2== retrieve->d[i].year) && (month2==retrieve->d[i].month) && (day2==retrieve->d[i].day))
					{
						found=1;
					}
					i++;
				}
				break;
			}
		case 2:
			{
				printf("Enter sensor type: ");
				scanf("%s",type);
				printf("Enter date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				while(strcmp(retrieve->sensor_type,type) !=0)
				{
					retrieve= retrieve->next;
				}
				while(found==0 && i<DAYS)
				{
					if((year2== retrieve->d[i].year) && (month2==retrieve->d[i].month) && (day2==retrieve->d[i].day))
					{
						for(j=0;j<RECORDS;j++)
						{
							printf("%f ",retrieve->d[i].data[j]);							
						}
						found=1;
					}
					i++;
				}
				break;				
												
			}
		case 31:
			{
				printf("Enter time interval\n");
				scanf("%f",&time2);
				printf("Enter sensor type\n");
				scanf("%s",type);
				printf("Enter date for which you have to check data\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				while(strcmp(retrieve->sensor_type,type) !=0)
				{
					retrieve= retrieve->next;
				}
				while((year2 != retrieve->d[i].year) && (month2 !=retrieve->d[i].month) && (day2 !=retrieve->d[i].day))
				{
					i++;
				}
				for(j=0;j<RECORDS && (found==0);j++)
				{
					if(retrieve->d[i].Time[j] == time2)
					{
						printf("%f",retrieve->d[i].data[j]);
						found=1;
					}
				}
				break;
			}
		case 32:
			{
				printf("Enter time interval\n");
				scanf("%f",&time2);
				printf("Enter sensor type\n");
				scanf("%s",type);
				printf("Enter starting date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				printf("Enter ending date\n");
				scanf("%d %d %d",&day3,&month3,&year3);
				while(strcmp(retrieve->sensor_type,type) !=0)
				{
					retrieve= retrieve->next;
				}
				while((year2 != retrieve->d[i].year) && (month2 !=retrieve->d[i].month) && (day2 !=retrieve->d[i].day))
				{
					i++;
				}
				while(( year3 <= retrieve->d[i].year) && (month3 <=retrieve->d[i].month) && (day3 <=retrieve->d[i].day))
				{
					for(j=0;j<RECORDS && (found==0);j++)
					{
						if(retrieve->d[i].Time[j] == time2)
						{
							printf("%f",retrieve->d[i].data[j]);
							found=1;
						}
					}
					i++;
				}
				break;								
			}
		default:
			{
				printf("Please enter correct method number\n");
				break;
			}
	}
}

void find_communicating_neighbours (sensor_node* head_ptr)
{ 
	int i=1;
	sensor_node* find = head_ptr;
	while(find != NULL)
	{
		printf("\nNeighbours group %d: ",i);
		while(find->station_dist < 10 && (find != NULL))
		{
			printf("%d->",find->sensor_id);
			find = find->next;
		}
		while(find->station_dist > 10 && (find != NULL))
		{
			find = find->next;
		}
		i++;	
	} 
}

void max_AQI(AQI* head_ptr)
{
	AQI* temp = head_ptr;
	int i,j,max=0,month4,year4;
	while(temp != NULL)
	{
		for(i=0;i<DAYS;i++)
		{
			if(max< temp->A[i].final_AQI)
			{
				max = temp->A[i].final_AQI;
				month4 = temp->A[i].month;
				year4 = temp->A[i].year; 
			}
		}
	}
	printf("In %d-%d maximum AQI was recorded",month4,year4);
}

void health_status(AQI* head_ptr)
{
	AQI* temp = head_ptr;
	int i,found=0;
	char status[50],loc5[20];
	printf("Enter health status\n");
	scanf("%s",status);
	printf("Enter sensor location");
	scanf("%s",loc5);
	while(strcmp(temp->sensor_loc,loc5) != 0)
	{
		temp = temp->next;
	}
	if(strcmp(status,"good")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=1) && (temp->A[i].final_AQI <=50) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}
	}
	else if(strcmp(status,"Satisfactory")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=51) && (temp->A[i].final_AQI <=100) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}		
	}
	else if(strcmp(status,"Moderately_polluted")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=101) && (temp->A[i].final_AQI <=200) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}				
	}
	else if(strcmp(status,"Poor")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=201) && (temp->A[i].final_AQI <=300) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}		
	}
	else if(strcmp(status,"May_cause_respiratory_illness")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=301) && (temp->A[i].final_AQI <=400) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}		
	}
	else if(strcmp(status,"Severe")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if((temp->A[i].final_AQI >=401) && (temp->A[i].final_AQI <=500) )
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}			
	}
	else if(strcmp(status,"Hazardous")==0)
	{
		for(i=0;i<DAYS;i++)
		{
			if(temp->A[i].final_AQI >=501)
			{
				printf("%d %d %d",temp->A[i].day,temp->A[i].month,temp->A[i].year);
			}
		}				
	}
		
}

void check_status(AQI* head_ptr)
{
	int i;
	AQI* temp = head_ptr;
	while(temp != NULL)
	{
		for(i=0;i<DAYS;i++)
		{
			if(temp->A[i].final_AQI >= 501)
			{
				printf("%d %d %d\n",temp->A[i].day,temp->A[i].month,temp->A[i].year);	
			}	
		}
		temp = temp->next;	
	}	 
}



int main()
{
	sensor_node* head = NULL;
	record* record_head =NULL;
	AQI* aqi_head = NULL;
	create_sensor_list(&head);
//	record_head = central_repository(head,record_head);
	head = install_new_sensor(head);
	idle_sensors(&record_head);
	find_communicating_neighbours (head);
	max_AQI(aqi_head);
	health_status(aqi_head);
	check_status( aqi_head);
}
