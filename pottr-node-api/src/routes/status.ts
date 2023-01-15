import Router from "koa-router";
import { z } from "zod";
import { handleError, handleValidation } from "../handlers";
import { StatusData } from "../types";

export const status = new Router({ prefix: "/status" });

const updateStatusSchema = z.object({
  body: z.object({
    planterID: z.string(),
    planterName: z.string(),
    online: z.boolean(),
    chargeLevel: z.number(),
  }),
});

status.post("/update-status", async (ctx, next) => {
  await handleValidation(updateStatusSchema, ctx);
  await handleError(async () => {
    await next();
    // Set Status
    const status = ctx.request.body as StatusData;
    console.log(status);
    ctx.response.body = {};
  }, ctx);
});
