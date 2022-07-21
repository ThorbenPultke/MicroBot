import numpy as np
import math 

class robot:
    def __init__(self):
        self.__n_axis = 5
        self.__links = np.array([95.6, 90.0, 56.2, 42.3])
        self.__angles  = [[-90, 90], [-90, 90], [-90, 90], [-90, 90], [-90, 90]]
        self.__angularVelocities = [None, None, None, None, None]
        self.__angularAcceleration = [None, None, None, None, None]

        self.__DHtheta = [0, -math.pi/2, 0, math.pi/2, 0]
        self.__DHalpha = [-math.pi/2, math.pi, math.pi, math.pi/2, 0]
        self.__DHd = [self.__links[0], 0, 0, 0, self.__links[3]]
        self.__DHa = [0, 0, self.__links[1] + self.__links[2], 0, 0]
        
        self.joints = []
        
        for i in range(self.__n_axis):
            self.joints.append(joint(num = i + 1,
                                     type = "R",
                                     angles = self.__angles[i],
                                     velocity = self.__angularVelocities[i],
                                     acceleration = self.__angularAcceleration[i],
                                     DHtheta = self.__DHtheta[i],
                                     DHalpha = self.__DHalpha[i],
                                     DHd = self.__DHd[i],
                                     DHa = self.__DHa[i]
                                     ))

    def start(self):
        pass

    def __connect_to_controller(self, COMPort: str = "COM3"):
        pass

    def __set_joint_angles(self, angles: list):
        if len(angles) != 5:
            raise Exception("Not enough angles provided.")
        else:
            for i, angle in enumerate(angles):
                self.joints[i].set_angle(angle)

    def calculate_forward_kinematics(self, angles: list, joint: int = 4):
        DHMatrizes = []
        self.__set_joint_angles(angles)
        T = []
        for i in range(self.__n_axis):
            DHMatrizes.append(self.joints[i].return_DH_Transformation_Matrix())
        T.append(DHMatrizes[0])
        T.append(T[0]@DHMatrizes[1])
        T.append(T[1]@DHMatrizes[2])
        T.append(T[2]@DHMatrizes[3])
        T.append(T[3]@DHMatrizes[4])
        return T[joint]

class joint:
    def __init__(self, num: int, type: str, angles: list, velocity: float, acceleration: float, DHtheta: float, DHalpha: float, DHd: float, DHa: float):
        self.__position = num
        self.__type = type
        self.__min_angle = min(angles)
        self.__max_angle = max(angles)
        self.__max_velocity = velocity
        self.__max_acceleration = acceleration

        self.__current_angle = 0.0
        self.__current_velocity = 0.0
        self.__current_acceleration = 0.0

        self.__DHtheta = DHtheta
        self.__DHalpha = DHalpha
        self.__DHd = DHd
        self.__DHa = DHa

        self.currentDHMatrix = np.array([])

    def set_angle(self, angle):
        self.__current_angle = angle

    def return_angle(self) -> float:
        return self.current_angle
    
    def return_DH_Transformation_Matrix(self, angle: float = 99999.9) -> np.ndarray:
        if angle == 99999.9:
            #Use internal current angle
            angle_rad = math.radians(self.__current_angle)
        else:
            angle_rad = math.radians(angle)
        usingTheta = self.__DHtheta + angle_rad

        Dh = np.array([[math.cos(usingTheta), -math.sin(usingTheta)*math.cos(self.__DHalpha), math.sin(usingTheta)*math.sin(self.__DHalpha), self.__DHa*math.cos(usingAngle)],
                       [math.sin(usingTheta), math.cos(usingTheta)*math.cos(self.__DHalpha), -math.cos(usingTheta)*math.sin(self.__DHalpha), self.__DHa*math.sin(usingTheta)],
                       [0, math.sin(self.__DHalpha), math.cos(self.__DHalpha), self.__DHd],
                       [0, 0, 0, 1]])

        self.currentDHMatrix = Dh
        return Dh


