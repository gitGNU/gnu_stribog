/*ad-hoc INS mechanization; should be rewritten completely
Copyright (C) 2006, 2007, 2008 Ineiev <ineiev@users.sourceforge.net>
This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#include"lege_lineam.h"
#include"error.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
static int gps_interval=9,/*every (gps_interval+1)th fix is taken into account*/
 gps_cycle_phase,/*counter for gps_interval*/
 fix_mag_corr;/*whether mag_corr is used*/
static long gps_fixes_processed;/*null when no GPS fix has been processed yet*/
static double mag_angle=-10,/*something like atan2(mag.y,mag.x)*/
 mag_corr,/*magnetic course correction from calibration data*/
 mag_corr_aest,/*magnetic course correction, estimated from velocity*/
 acc=0,tacc=-1,acc_meas[3],dt_acc,
 _delta,_k,pr_acc[3],pr_norm_acc,delta,k,gyro_0=1980,gyro_k=0.025,gyro_angle,
 hodo_k=.2,dhodo,dthodo,hodo_angle=7;
static enum{magnetic_source,gyro_source}hodo_angle_source=magnetic_source;
static const int k_calib=1,delta_calib=2;
static int _acc_calib,acc_calib,gyro_calib,hodo_calib;
/*x-ortus,y-septentriones,z-vertex*/
typedef struct{double t,x,y,z,vx,vy,vz;}positio;
static long mag_bias[2],mag_scale[2];
static positio pos={-1,0,0,0,0,0,0},ex={-1,0,0,0,0,0,0},gy={-1,0,0,0,0,0,0},
 hod={-1,0,0,0,0,0,0},
 gps_offset={0,0,0,0,0,0,0}/*this will be subtracted from GPS position input*/;
static void
printf_pos(const positio*p)
{printf("%f ",p->t);printf("%f %f %f ",p->x,p->y,p->z);
 printf("%f %f %f",p->vx,p->vy,p->vz);
}
static void
proc_vel(const char*s)
{positio pr=pos;double dt;static int vex=0,i;
 sscanf(s,"%lf",&dt);if(dt<-.5)return;
 sscanf(s,"%lf %lf %lf %lf %lf %lf %lf",
  &pos.t,&pos.x,&pos.y,&pos.z,&pos.vx,&pos.vy,&pos.vz);
 printf("xvel_original: %s\n",s);
 pos.t-=gps_offset.t;
 pos.x-=gps_offset.x;pos.y-=gps_offset.y;pos.z-=gps_offset.z;
 pos.vx-=gps_offset.vx;pos.vy-=gps_offset.vy;pos.vz-=gps_offset.vz;
 printf("xvel: ");printf_pos(&pos);printf("\n");
 dt=pos.t-pr.t;
 if(pr.t>0)
 {printf("dxyz: %f %f %f %f %f %f %f\n",
   pos.t,pos.x-pr.x,pos.y-pr.y,pos.z-pr.z,pos.vx*dt,pos.vy*dt,pos.vz*dt);
  printf("extra_gps: %f %f %f %f %f %f %f\n",
    pos.t,pr.x+pr.vx*dt,pr.y+pr.vy*dt,pr.z+pr.vz*dt,pos.vx,pos.vy,pos.vz);
 }else return;
 {double v=sqrt(pos.vx*pos.vx+pos.vy*pos.vy);
  if(v>2)
  {double _=atan2(pos.vy,pos.vx),a=_;mag_corr_aest=a-mag_angle;
   printf("v_angle: %f %f %f",pos.t,v,a);a=mag_angle-a;
   if(a>M_PI)a-=2*M_PI;if(a<-M_PI)a+=2*M_PI;printf(" %f",a);
   a=gyro_angle-_;
   if(a>M_PI)a-=2*M_PI;if(a<-M_PI)a+=2*M_PI;printf(" %f\n",a);
   a=hodo_angle-_;
   if(a>M_PI)a-=2*M_PI;if(a<-M_PI)a+=2*M_PI;printf(" %f\n",a);
  }
 }
 if(tacc>0)
 {double dv[3],p,v;*dv=pos.vx-pr.vx;dv[1]=pos.vy-pr.vy;dv[2]=pos.vz-pr.vz;
  for(i=0;i<3;i++)dv[i]/=dt;
  p=*dv*pos.vx+dv[1]*pos.vy+dv[2]*pos.vz;v=sqrt(pos.vx*pos.vx+pos.vy*pos.vy+pos.vz*pos.vz);
  if(v<.01)p=0;else p/=v;
  for(i=0;i<3;i++)acc_meas[i]*=1+(pos.t-tacc)/dt_acc;dt_acc+=pos.t-tacc;
  if(dt_acc>.01)for(i=0;i<3;i++)acc_meas[i]/=dt_acc;
  printf("dt_acc: %f %f\n",dt_acc,pos.t-tacc);
  printf("norm_acc: %f %f %f %f %f\n",pr_norm_acc,p,acc_meas[0],acc_meas[1],acc_meas[2]);
  if(fabs(pr_norm_acc-p)>.2)/*if(fabs(acc_meas[1]-pr_acc[1])>.5/40)*/
  {_k=(pr_norm_acc-p)/(pr_acc[1]-acc_meas[1]);_acc_calib|=k_calib;
   printf("k_acc: %f %f\n",pos.t,_k);
  }
  if(fabs(pr_norm_acc-p)>.2)
  {_delta=(pr_norm_acc*acc_meas[1]-p*pr_acc[1])/(p-pr_norm_acc);_acc_calib|=delta_calib;
   printf("delta_acc: %f %f\n",pos.t,_delta);
  }
  if(k>1e-7){_delta=p/k-acc_meas[1];printf("delta_acc_bis: %f %f\n",pos.t,_delta);}
  pr_norm_acc=p;
  for(i=0;i<3;i++){pr_acc[i]=acc_meas[i];acc_meas[i]=0;}tacc=pos.t;dt_acc=0;
 }acc=0;vex=!0;
 {if(gps_cycle_phase++>=gps_interval)
  {double _;gps_cycle_phase=0;
   ex.x+=(pos.t-ex.t)*ex.vx;ex.y+=(pos.t-ex.t)*ex.vy;ex.z+=(pos.t-ex.t)*ex.vz;
   _=ex.t;ex.t=pos.t;printf("extra_pos: ");printf_pos(&ex);printf("\n");ex.t=_;
   printf("extra_error: %f %f %f %f %f %f %f %f %f\n",pos.t,
    ex.x-pos.x,ex.y-pos.y,ex.z-pos.z,ex.vx-pos.vx,ex.vy-pos.vy,ex.vz-pos.vz,
    sqrt((ex.x-pos.x)*(ex.x-pos.x)+(ex.y-pos.y)*(ex.y-pos.y)+(ex.z-pos.z)*(ex.z-pos.z)),
    sqrt((ex.vx-pos.vx)*(ex.vx-pos.vx)+(ex.vy-pos.vy)*(ex.vy-pos.vy)+
     (ex.vz-pos.vz)*(ex.vz-pos.vz)));
   {double v=sqrt(pos.vx*pos.vx+pos.vy*pos.vy),vx,vy,ert,ern,erx,ery;
    if(v>0.3&&gps_fixes_processed>0)
    {vx=pos.vx/v;vy=pos.vy/v;
     erx=ex.x-pos.x;ery=ex.y-pos.y;ern=erx*vx+ery*vy;ert=erx*vy-ery*vx;
     printf("trans_tang_error: %f %f %f\n",pos.t,ern,ert);
    }
   }ex=pos;
   gy.x+=(pos.t-gy.t)*gy.vx;gy.y+=(pos.t-gy.t)*gy.vy;gy.z+=(pos.t-gy.t)*gy.vz;
   _=gy.t;gy.t=pos.t;printf("extra_gyro_pos: ");
   printf_pos(&gy);printf("\n");gy.t=_;
   printf("gyro_error: %f %f %f %f %f %f %f %f %f\n",pos.t,
    gy.x-pos.x,gy.y-pos.y,gy.z-pos.z,gy.vx-pos.vx,gy.vy-pos.vy,gy.vz-pos.vz,
    sqrt((gy.x-pos.x)*(gy.x-pos.x)+(gy.y-pos.y)*(gy.y-pos.y)+(gy.z-pos.z)*(gy.z-pos.z)),
    sqrt((gy.vx-pos.vx)*(gy.vx-pos.vx)+(gy.vy-pos.vy)*(gy.vy-pos.vy)+
     (gy.vz-pos.vz)*(gy.vz-pos.vz)));
   {double v=sqrt(pos.vx*pos.vx+pos.vy*pos.vy),vx,vy,ert,ern,erx,ery;
    if(v>0.3&&gps_fixes_processed>0)
    {vx=pos.vx/v;vy=pos.vy/v;
     erx=gy.x-pos.x;ery=gy.y-pos.y;ern=erx*vx+ery*vy;ert=erx*vy-ery*vx;
     printf("gyro_trans_tang_error: %f %f %f\n",pos.t,ern,ert);
    }
   }gy=pos;if(fabs(pos.vy)+fabs(pos.vx)>1)gyro_angle=atan2(pos.vy,pos.vx);else gyro_angle=10;
   hod.x+=(pos.t-hod.t)*hod.vx;hod.y+=(pos.t-hod.t)*hod.vy;hod.z+=(pos.t-hod.t)*hod.vz;
   if(gps_fixes_processed)
   {_=hod.t;hod.t=pos.t;printf("extra_hodo_pos: ");
    printf_pos(&hod);printf("\n");hod.t=_;
    printf("hodo_error: %f %f %f %f %f %f %f %f %f\n",pos.t,
     hod.x-pos.x,hod.y-pos.y,hod.z-pos.z,hod.vx-pos.vx,hod.vy-pos.vy,hod.vz-pos.vz,
     sqrt((hod.x-pos.x)*(hod.x-pos.x)+(hod.y-pos.y)*(hod.y-pos.y)+(hod.z-pos.z)*(hod.z-pos.z)),
     sqrt((hod.vx-pos.vx)*(hod.vx-pos.vx)+(hod.vy-pos.vy)*(hod.vy-pos.vy)+
      (hod.vz-pos.vz)*(hod.vz-pos.vz)));
   }
   {double v=sqrt(pos.vx*pos.vx+pos.vy*pos.vy),vx,vy,ert,ern,erx,ery;
    if(v>0.3&&gps_fixes_processed>0)
    {vx=pos.vx/v;vy=pos.vy/v;
     erx=hod.x-pos.x;ery=hod.y-pos.y;ern=erx*vx+ery*vy;ert=erx*vy-ery*vx;
     printf("hodo_trans_tang_error: %f %f %f\n",pos.t,ern,ert);
    }
   }hod=pos;if(fabs(pos.vy)+fabs(pos.vx)>1)hodo_angle=atan2(pos.vy,pos.vx);else hodo_angle=10;
   gps_fixes_processed++;
  }
 }
}
static double
mag_correction(void)
{if(fix_mag_corr)return mag_corr;return mag_corr_aest;}
static void
proc_acc(const char*s)
{static double t,a[3],w[3],t0,meas[3],dt,mag[3];int i;
 sscanf(s,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&t,a,a+1,a+2,mag,mag+1,mag+2,
  w,w+1,w+2);dt=t-tacc;
 {mag_angle=atan2((double)(mag[0]-mag_bias[0])/mag_scale[0],
    (double)(mag[1]-mag_bias[1])/mag_scale[1])-mag_correction();
  if(mag_angle>M_PI)mag_angle-=2*M_PI;if(mag_angle<-M_PI)mag_angle+=2*M_PI;
  printf("mag_angle: %f %f\n",t,mag_angle);
 }
 if(tacc<0){t0=tacc=t;for(i=0;i<3;meas[i++]=0);return;}
 for(i=0;i<3;i++){acc_meas[i]+=dt*a[i];meas[i]+=dt*a[i];}dt_acc+=dt;tacc=t;
 if(tacc-t0>1)
 {printf("acc_meas: %f %f %f %f\n",tacc,meas[0]/(tacc-t0),meas[1]/(tacc-t0),meas[2]/(tacc-t0));
  t0=tacc;for(i=0;i<3;meas[i++]=0);
 }if(!gps_fixes_processed)return;
 if(acc_calib&&ex.t>0)
 {double ang=mag_angle,
  dv=k*(a[0]-delta)*dt,v=sqrt(ex.vx*ex.vx+ex.vy*ex.vy)+dv;
  ex.vx=cos(ang)*v;ex.vy=sin(ang)*v;ex.t=tacc;ex.x+=ex.vx*dt;ex.y+=ex.vy*dt;
  printf("acc_pos: ");printf_pos(&ex);printf("\n");
 }
 if(gyro_calib&&gy.t>0&&gyro_angle<7)
 {double ang=gyro_angle,dv=k*(a[0]-delta)*dt,v=sqrt(gy.vx*gy.vx+gy.vy*gy.vy)+dv;
  gyro_angle+=(w[2]-gyro_0)*gyro_k*dt;
  gy.vx=cos(ang)*v;gy.vy=sin(ang)*v;gy.t=tacc;gy.x+=gy.vx*dt;gy.y+=gy.vy*dt;
  printf("gyro_pos: ");printf_pos(&gy);printf(" %f %f %f\n",gyro_angle,v,dv);
 }
 if(hodo_angle_source==gyro_source)if(gyro_calib&&hod.t>0&&hodo_angle<7)
  hodo_angle+=(w[2]-gyro_0)*gyro_k*dt;
 if(hodo_angle_source==magnetic_source)if(hodo_calib)hodo_angle=mag_angle;
}
static void
proc_hodo(const char*s)
{static unsigned long h0;unsigned long h;static int t0=-1;unsigned t;
 static const double thscale=21735.77;static double temp0;
 double dh=0,dt=0,temp;
 printf("odo: %s\n",s);sscanf(s,"%lf %i %lu",&temp,&t,&h);
 if(t0>0&&temp0!=temp)
 {dhodo+=(dh=(h-h0)*hodo_k);if(t<t0)t+=1<<16;dthodo+=(dt=(t-t0)/thscale);}
 else dthodo=dhodo=0;
 t0=t;h0=h;hod.t=temp;
 if(hodo_angle<7&&temp0!=temp)
 {hod.x+=dh*cos(hodo_angle);hod.y+=dh*sin(hodo_angle);
  if(dt>0){hod.vx=dh/dt*cos(hodo_angle);hod.vy=dh/dt*sin(hodo_angle);}
  printf("hodo_pos: ");printf_pos(&hod);
  printf(" %f %f %f\n",hodo_angle,dh,dt);
 }temp0=temp;
}
static void
proc_magb(const char*s)
{sscanf(s,"%*f %li %li %li %li",mag_bias,mag_bias+1,mag_scale,mag_scale+1);
 printf("mag.bias: %li %li %li %li\n",*mag_bias,mag_bias[1],*mag_scale,mag_scale[1]);
}
static void
proc_magc(const char*s)
{sscanf(s,"%*f %lf",&mag_corr);printf("mag.corr: %f\n",mag_corr);}
static void
proc_mag(const char*s)
{long mag[2];double t;sscanf(s,"%lf %li %li",&t,mag,mag+1);
 mag_angle=atan2((double)(mag[0]-mag_bias[0])/mag_scale[0],
    (double)(mag[1]-mag_bias[1])/mag_scale[1])-mag_correction();
 if(mag_angle>M_PI)mag_angle-=2*M_PI;if(mag_angle<-M_PI)mag_angle+=2*M_PI;
 printf("mag_angle: %f %f\n",t,mag_angle);
}
static void
proc_accalib(const char*s)
{double x[4];int n;printf("acc calib: %s\n",s);
 /*as of Jan 2008 we use x-axis accelerometer only*/
 n=sscanf(s,"%lf"" %lf %lf %lf %lf %lf %lf",x+1,x+2,x+3,x,x,x,x);
 if(n<6){error("too few acc_calib arguments");return;}
 if(n==7){/*uniform timestamp at the first position*/delta=x[2];k=x[3];}
 else{/*deprecated format: without time*/delta=x[1];k=x[2];}
 printf("acc.calib: delta=%f k=%f\n",delta,k);
 acc_calib|=k_calib|delta_calib;
}
static void
proc_gyrocalib(const char*s)
{double x[4];int n;printf("gyro calib: %s\n",s);
 /*as of Jan 2008 we use z-axis angular rate sensor only*/
 n=sscanf(s,"%lf"" %lf %lf %lf %lf %lf %lf",x,x,x,x,x+1,x+2,x+3);
 if(n<6){error("too few gyro_calib arguments");return;}
 if(n==7){/*uniform timestamp at the first position*/gyro_0=x[2];gyro_k=x[3];}
 else{/*deprecated format: without time*/gyro_0=x[1];gyro_k=x[2];}
 printf("gyro.calib: gyro_0=%f k=%f\n",gyro_0,gyro_k);
 gyro_calib=!0;
}
static void
proc_hodo_calib(const char*s)
{char src;printf("hodo calib: %s\n",s);sscanf(s,"%*f %lf %c",&hodo_k,&src);hodo_calib=!0;
 hodo_angle_source=magnetic_source;
}
static void
proc_hodo_angle_src(const char*s)
{char src;printf("hodo angle source: %s\n",s);sscanf(s,"%*f %c",&src);
 hodo_angle_source=magnetic_source;if(src=='g')hodo_angle_source=gyro_source;
 printf("hodo.ang.src: %c\n",hodo_angle_source==gyro_source?'g':'m');
}
static int
arg_cmp_val(const char*arg,const char*cmd,const char**value)
{static const char broadcast[]="broadcast";int n=strlen(broadcast);
 if((arg[n]==' '||!arg[n])&&strncmp(broadcast,arg,n))return 0;
 n=strlen(cmd);if(arg[n]!=' '&&arg[n]!='='&&arg[n])return!0;
 if(strncmp(arg,cmd,n))return!0;
 if(value){if(arg[n]=='=')*value=arg+n+1;else*value=0;}
 return 0;
}
static int
arg_cmp(const char*arg,const char*cmd){return arg_cmp_val(arg,cmd,0);}
enum action_sign
{neutral_action,disable_option,enable_option,toggle_option,show_option};
static const char*
skip_field(const char*s)
{while(*s&&*s!=' ')s++;while(*s&&*s==' ')s++;return s;}
static const char*
next_alg_ctl_arg(const char*s,enum action_sign*sign)
{*sign=neutral_action;s=skip_field(s);
 switch(*s)
 {case'-':*sign=disable_option;s++;break;
  case'+':*sign=enable_option;s++;break;
  case'%':*sign=toggle_option;s++;break;
  case'@':*sign=show_option;s++;break;
 }if(!*s)return 0;return s;
}
static void
fix_mag_corr_action(double t,enum action_sign sign)
{printf("#fix_mag_corr_action: %f ",t);
 switch(sign)
 {case neutral_action:case enable_option:
   fix_mag_corr=!0;printf("enabled\n");break;
  case disable_option:
   fix_mag_corr=0;printf("disabled\n");break;
  case toggle_option:
   fix_mag_corr=!fix_mag_corr;
   printf("toggled (%i->%i)\n",!fix_mag_corr,fix_mag_corr);break;
  case show_option:
   printf("shown %i\n",fix_mag_corr);break;
  default:printf("no such action sence\n");
 }
}
static void
set_gps_interval(double t,enum action_sign sign,const char*value)
{printf("#gps_interval: %f ",t);
 switch(sign)
 {case show_option:printf("%i\n",gps_interval);break;
  case neutral_action:
   if(!value){printf("no value\n");break;}
   {double x;
    if(1!=sscanf(value,"%lf",&x)){printf("wrong value\n");break;}
    printf("%i->",gps_interval);
    gps_interval=x;printf("%i\n",gps_interval);
   }break;
  default:printf("no such action sence\n");
 }
}
static void
set_gps_cycle_phase(double t,enum action_sign sign,const char*value)
{printf("#gps_cycle_phase: %f ",t);
 switch(sign)
 {case show_option:printf("%i\n",gps_cycle_phase);break;
  case neutral_action:if(!value){printf("no value\n");break;}
  {double x;
   if(1!=sscanf(value,"%lf",&x)){printf("wrong value\n");break;}
   printf("%i->",gps_cycle_phase);
   gps_cycle_phase=x;printf("%i\n",gps_cycle_phase);
  }break;
  default:printf("no such action sence\n");
 }
}
static void
set_gps_offset(double t,enum action_sign sign,const char*value)
{positio*p=&gps_offset;
 printf("#gps_position_offset: %f ",t);
 switch(sign)
 {case show_option:printf_pos(p);printf("\n");break;
  case neutral_action:if(!value){printf("no value\n");break;}
  {positio x;
   if(7!=sscanf(value,"%lf,%lf,%lf,%lf,%lf,%lf,%lf",
      &(x.t),&(x.x),&(x.y),&(x.z),&(x.vx),&(x.vy),&(x.vz)))
   {printf("wrong value '%s'\n",value);break;}
   printf("(");printf_pos(p);printf(")->(");
   printf("(");printf_pos(&x);printf("\n");*p=x;
  }break;
  default:printf("no such action sence\n");
 }
}
static void
algorithm_control(const char*s)
{enum action_sign sign;double t;const char*value;
 printf("alg.control: %s\n",s);
 if(1!=sscanf(s,"%lg",&t)){error("no time assigned");return;}
 s=skip_field(s);
 while((s=next_alg_ctl_arg(s,&sign)))
 {if(!arg_cmp(s,"fix_mag_corr"))fix_mag_corr_action(t,sign);
  if(!arg_cmp_val(s,"gps_interval",&value))set_gps_interval(t,sign,value);
  if(!arg_cmp_val(s,"gps_cycle_phase",&value))
   set_gps_cycle_phase(t,sign,value);
  if(!arg_cmp_val(s,"gps_position_offset",&value))
   set_gps_offset(t,sign,value);
 }
}
static void
explica(commentarium c,const char*s)
{switch(c)
 {case xpos_com:proc_vel(s);break;case mag_com:proc_mag(s);break;
  case mag_corr_com:proc_magc(s);break;case mag_bias_com:proc_magb(s);break;
  case acc_calib_com:proc_accalib(s);break;case gyro_calib_com:proc_gyrocalib(s);break;
  case hodo_calib_com:proc_hodo_calib(s);break;
  case gyro_com:proc_acc(s);break;case hodo_com:proc_hodo(s);break;
  case hodo_angle_source_com:proc_hodo_angle_src(s);break;
  case alg_control_com:algorithm_control(s);break;
  default:break;
 }
}
int
main(int argc,char**argv)
{const char*s;commentarium c;if(argc>1)sscanf(argv[1],"%i",&gps_interval);
 while((c=lege_lineam(&s))!=fin_com)if(s)explica(c,s);return 0;
}
