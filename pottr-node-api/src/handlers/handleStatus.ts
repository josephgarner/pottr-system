import { planterDetails } from "../db/models/planterDetails";
import { StatusData } from "../types";

export const handleStatus = async (data: StatusData) => {
  console.info(
    `Saving status for planter - ${data.planterID} ${data.planterName} - ${data.online}`
  );
  console.log(data);
  await planterDetails.updateOne(
    { planterID: data.planterID },
    {
      $set: {
        online: data.online,
        planterName: data.planterName,
        lastOnline: new Date(),
      },
    },
    { upsert: true }
  );
};
