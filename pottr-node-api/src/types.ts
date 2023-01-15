export type PlanterDetails = {
  planterID: string;
  planterName: string;
  online: boolean;
  lastOnline: Date | null;
  title?: string | null;
  highestReading: number;
  lowestReading: number;
  triggerUpperLimit?: number | null;
  triggerLowerLimit?: number | null;
  dateCreated: Date | null;
};

export type MoistureData = {
  planterID: string;
  planterName: string;
  moistureReading: number;
  irrigating: boolean;
  dateReceived?: Date;
};

export type BatteryData = {
  planterID: string;
  planterName: string;
  chargeLevel: number;
  dateReceived?: Date;
};

export type StatusData = {
  planterID: string;
  planterName: string;
  online: boolean;
  chargeLevel: number;
  dateReceived?: Date;
};

export type CommandQueue = {
  planterID: string;
  issuedCommand: string;
  sent?: boolean;
  actioned?: boolean;
  dateCreated?: Date;
  dateUpdated?: Date;
};

export enum CommandType {
  IRRIGATE = "IRRIGATE",
  STOP_IRRIGATE = "STOP_IRRIGATE",
  IRRIGATE_MAX = "IRRIGATE_MAX",
  NOTHING_TO_DO = "NOTHING_TO_DO",
}

export enum SEASONS {
  SUMMER_EARLY = "Early Summer",
  SUMMER = "Summer",
  SUMMER_LATE = "Late Summer",
  AUTUMN_EARLY = "Early Autumn",
  AUTUMN = "Autumn",
  AUTUMN_LATE = "Late Autumn",
  WINTER_EARLY = "Early Winter",
  WINTER = "Winter",
  WINTER_LATE = "Late Winter",
  SPRING_EARLY = "Early Spring",
  SPRING = "Spring",
  SPRING_LATE = "Late Spring",
}

export type GrowingTime = {
  min: number;
  max: number;
};

export type Vegetation = {
  name: string;
  sow: Array<SEASONS>;
  harvest: Array<SEASONS>;
  growing: GrowingTime;
};

export type PlanterVegetationList = {
  planterID: string;
  datePlanted?: Date;
  vegetation: Vegetation;
  harvested?: boolean;
};
