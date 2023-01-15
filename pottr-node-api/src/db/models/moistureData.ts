import mongoose from "mongoose";
import { MoistureData } from "../../types";

const moistureDataSchema = new mongoose.Schema({
  planterID: {
    type: String,
    required: true,
  },
  moistureReading: {
    type: Number,
    required: true,
  },
  irrigating: {
    type: Boolean,
    required: true,
  },
  dateReceived: {
    type: Date,
    required: true,
    default: new Date(),
  },
});

moistureDataSchema.statics.build = (attr: MoistureData) => {
  return new moistureData(attr);
};

interface moistureDataModel extends mongoose.Model<any> {
  build(attr: MoistureData): any;
}

const moistureData = mongoose.model<any, moistureDataModel>(
  "MoistureData",
  moistureDataSchema
);

export { moistureData };
