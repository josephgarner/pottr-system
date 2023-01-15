import { batteryData } from "../db/models/batteryData";
import { BatteryData } from "../types";

export const handleBatteryStatus = async (battery: BatteryData) => {
  console.info(
    `Saving battery info for - ${battery.planterID} ${battery.planterName}`
  );
  const report = batteryData.build({ ...battery, dateReceived: new Date() });
  await report.save();
};
