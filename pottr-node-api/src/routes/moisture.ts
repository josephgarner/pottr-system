import Router from "koa-router";
import { z } from "zod";
import { handleError, handleValidation } from "../handlers";
import { MoistureData } from "../types";

export const moisture = new Router({ prefix: "/moisture" });

const updateStatusSchema = z.object({
  body: z.object({
    planterID: z.string(),
    planterName: z.string(),
    moistureReading: z.number(),
    irrigating: z.boolean(),
  }),
});

moisture.post("/report", async (ctx, next) => {
  await handleValidation(updateStatusSchema, ctx);
  await handleError(async () => {
    await next();
    const moisture = ctx.request.body as MoistureData;
    console.log(moisture);
    ctx.response.body = {};
  }, ctx);
});
