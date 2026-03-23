import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
def get_hist(path_val,density_val):
    df = pd.read_csv(path_val,encoding="utf-8")
    df['Energy']=pd.to_numeric(df['Energy'])
    df['Counts']=pd.to_numeric(df['Counts'])
    data=df['Counts']
    ID=df['Energy']
    plt.plot()
    data=data/sum(data)
    # hist=hist/sum(hist)
    return (ID,data)
def plot_spectrum(path_val,legend_val,color_val,density_val,line_val):
    ID,data=get_hist(path_val,density_val)
    # save_data={
        # 'Counts':hist,
        # 'Energy':bin_edges[:-1]
    # }
    # df=pd.DataFrame(save_data)
    # df.to_csv(save_val,index=False)
    plt.plot(ID,data,color = color_val,label=legend_val,linewidth=1.5,linestyle=line_val)
    plt.xlim(0,140)
    return
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\362.csv",'20cm','green',True,'-')
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\366.csv",'40cm','red',True,'-')
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\370.csv",'60cm','blue',True,'-')
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\374.csv",'80cm','yellow',True,'-')
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\378.csv",'100cm','purple',True,'-')
plot_spectrum(r"D:\program\cpp\geant4\data\csv_data\database\spectrum\12noise\Al\380.csv",'120cm','brown',True,'-')

prob=pd.read_csv(r"D:\program\cpp\geant4\config\Xray@225kVp.csv",encoding="utf-8")
prob['probability']=pd.to_numeric(prob['probability'])
prob['energy']=pd.to_numeric(prob['energy'])
in_prob=prob['probability']
in_energy=prob['energy']


# plt.plot(in_energy,in_prob,label='225kVp X-ray ',color='green')


plt.xlabel('Relative Energy/keV',fontsize=12, weight='bold')
plt.ylabel('Counts',fontsize=12, weight='bold')
plt.legend(fontsize=14)
plt.xticks(fontsize=12, weight='bold')
plt.yticks(fontsize=12, weight='bold')
plt.grid()
plt.show()