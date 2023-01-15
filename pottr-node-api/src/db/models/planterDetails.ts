import mongoose from "mongoose";
import { PlanterDetails } from "../../types";

const planterDetailsSchema = new mongoose.Schema({
  planterID: {
    type: String,
    required: true,
  },
  planterName: {
    type: String,
    required: true,
  },
  online: {
    type: Boolean,
    default: false,
    required: true,
  },
  title: {
    type: String,
    default: null,
    required: false,
  },
  highestReading: {
    type: Number,
    default: 0,
    required: false,
  },
  lowestReading: {
    type: Number,
    default: 0,
    required: false,
  },
  triggerUpperLimit: {
    type: Number,
    default: null,
    required: false,
  },
  triggerLowerLimit: {
    type: Number,
    default: null,
    required: false,
  },
  plants: {
    type: String,
    default: null,
    required: false,
  },
  lastOnline: {
    type: Date,
    default: new Date(),
    required: false,
  },
  dateCreated: {
    type: Date,
    default: new Date(),
    required: false,
  },
});

planterDetailsSchema.statics.build = (attr: PlanterDetails) => {
  return new planterDetails(attr);
};

interface planterDetailsModel extends mongoose.Model<any> {
  build(attr: PlanterDetails): any;
}

const planterDetails = mongoose.model<any, planterDetailsModel>(
  "PlanterDetails",
  planterDetailsSchema
);

export { planterDetails };
