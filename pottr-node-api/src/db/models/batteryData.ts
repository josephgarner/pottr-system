import mongoose from "mongoose";
import { BatteryData } from "../../types";

const batteryDataSchema = new mongoose.Schema({
  planterID: {
    type: String,
    required: true,
  },
  charge: {
    type: Number,
    required: true,
  },
  dateReceived: {
    type: Date,
    required: false,
    default: new Date(),
  },
});

batteryDataSchema.statics.build = (attr: BatteryData) => {
  return new batteryData(attr);
};

interface batteryDataModel extends mongoose.Model<any> {
  build(attr: BatteryData): any;
}

const batteryData = mongoose.model<any, batteryDataModel>(
  "BatteryData",
  batteryDataSchema
);

export { batteryData };
