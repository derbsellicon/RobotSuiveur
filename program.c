/*
 * =====================================================================================
 *
 *       Filename:  RobotSuiveur.c
 *
 *    Description:  Program du Robot Suiver 
 *
 *        Version:  1.0
 *        Created:  03/02/2014 12:41:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fatima-Zahra ITTOBANE, <fatima.zahra.ittobane@gmail.com>
 *        Company:  DerbSellicon 
 *
 * =====================================================================================
 */

#define pow 70

#define ref 80 

int gau=0,dro=0,mil=0;

int bon1=0,bon2=0;

int bon3=0;

void turgau() 
{
	motor(0,0); 
	motor(1,pow);
}

void turdro()
{
	motor(0,pow); 
	motor(1,0); 
}

void direct()
{
	motor(0,pow); 
	motor(1,pow);
}

int blanc(int b)
{
	int reff=80;

	if (b<reff)    
		return 0;
	else
		return 1;
}

void capteurs(int *gau,int *mil,int *dro,int *bon1,int *bon2,int *bon3)
{
	*gau  = analog(27); 
	*mil  = analog(25); 
	*dro  = analog(23); 
	*bon1 = analog(17); 
	*bon2 = analog(16);
	*bon3 = analog(18);
}

void pricipal(int *gau,int *mil,int *dro)    
{
	capteurs(gau,mil,dro,&bon1,&bon2,&bon3);

	if ( (blanc(*gau)  && !blanc(*mil) && blanc(*dro))  ||
		 (!blanc(*gau) && !blanc(*mil) && !blanc(*dro)) || 
		 (!blanc(*gau) && !blanc(*mil) && blanc(*dro))  || 
		 (blanc(*gau)  && !blanc(*mil) && !blanc(*dro))) 
	{
		direct();
	}

	else if( (!blanc(*gau) && blanc(*mil) && blanc(*dro)) ||
			 (!blanc(*gau) && blanc(*mil) && !blanc(*dro)) )
	{
		turgau();
	}

	else if((blanc(*gau) && blanc(*mil) && !blanc(*dro)))
	{
		turdro();
	}
}

void bonus(int *gau,int *mil,int *dro)
{
	direct();

	sleep(1.5);
	motor(1,0);
	motor(0,0);
	sleep(3.0);
	capteurs(gau,mil,dro,&bon1,&bon2,&bon3);

	if(blanc(*gau) && blanc(*mil) && blanc(*dro))
	{ 
		capt_init();  
	}
}


void capt_init()
{
	int c=0;

	capteurs(&gau,&mil,&dro,&bon1,&bon2,&bon3);

	while(blanc(gau) && blanc(mil) && blanc(dro) && c<60)
	{
		capteurs(&gau,&mil,&dro,&bon1,&bon2,&bon3);
		turgau();
		c++;
	}

	c=0;

	while(blanc(gau) && blanc(mil) && blanc(dro) && c<120)
	{
		capteurs(&gau,&mil,&dro,&bon1,&bon2,&bon3);
		turdro();
		c++;
	}
	//ao();
}


void main(void)
{
	ao();

	while(1) 
	{
		capteurs(&gau,&mil,&dro,&bon1,&bon2,&bon3);

		if(!blanc(bon1))
		{
			if(!blanc(bon2) && !blanc(bon3))
			{
				bonus(&gau,&mil,&dro);
			}
		}
		pricipal(&gau,&mil,&dro);
	}
}
