# Realidad Virtual
VR projecto para la catedra de realidad virtual de la Universidad Nacional de Cuyo.

## Instalación
Para la camara instalar [libuvc_camera](https://wiki.ros.org/libuvc_camera) y [usb-cam](https://wiki.ros.org/usb_cam) packages:

```bash
sudo apt-get install ros-melodic-libuvc-camera
sudo apt-get install ros-melodic-usb-cam
```

Luego para probar la instalacion:

```bash
roslaunch usb_cam-test.launch
```
Para la deteccion y el seguimiento de marcadores utilizo el paquete de [ar_track_alvar](http://wiki.ros.org/ar_track_alvar):

```bash
sudo apt-get install ros-melodic-ar-track-alvar 
```
Finalmente clonar el repositorio:

```bash
git clone https://github.com/jerepino/raspimouse_ws.git
```

## Uso
Lanzar los siguientes nodos en terminales diferentes:

```bash
1- roslaunch raspimouse_description simulation.launch
2- roslaunch raspimouse_description ras_ar_track.launch
3- roslaunch raspimouse_navigation navigation.launch
4- rosrun simple_navigation_goals pose_listener
```

## Acknowledgment
I used [rt-net/raspimouse_description](https://github.com/rt-net/raspimouse_description) repository. I have made little changes for my project
